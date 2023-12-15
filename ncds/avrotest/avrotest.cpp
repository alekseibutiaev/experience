#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <optional>
#include <iterator>
#include <memory>
#include <vector>
#include <thread>
#include <chrono>

#include <avro/Generic.hh>
#include <avro/Schema.hh>
#include <avro/ValidSchema.hh>
#include <avro/Compiler.hh>
#include <avro/Encoder.hh>
#include <avro/Decoder.hh>
#include <avro/Specific.hh>


#include <print_records.h>

namespace {

  using buffer_t = std::vector<unsigned char>;
  using buffer_try_t = std::optional<buffer_t>;
  using valid_schema_ptr = std::shared_ptr<avro::ValidSchema>;

  valid_schema_ptr load(std::istream& is) {
    std::string error;
    valid_schema_ptr schema = std::make_shared<valid_schema_ptr::element_type>();
    avro::compileJsonSchema(is, *schema, error);
    return schema;
  }

  valid_schema_ptr load(const std::string& file) {
    if(auto ifs = std::ifstream(file.c_str()))
      return load(ifs);
    throw(std::runtime_error("can`t open file: " + file));
  }

  buffer_try_t load(const std::string& prefix, std::size_t idx, const std::string& suffix) {
    std::ostringstream oss;
    oss << prefix << std::setfill('0') << std::setw(8) << idx << suffix;
    const std::string& name = oss.str();
    buffer_try_t res;
    if(auto ifs = std::ifstream(oss.str()))
      res = buffer_t(std::istream_iterator<buffer_t::value_type>(ifs), std::istream_iterator<buffer_t::value_type>());
    return res;
  }

  void evidence(const std::string& str, const buffer_try_t& buf) {
    if(!buf)
      return;
    // show buffer
    pbuffer(buf->data(), buf->size());
    try {
      // create ctream for read schema
      auto iss = std::istringstream(str);
      // 
      if(const auto& schema = load(iss)) {
        const auto leaves = schema->root()->leaves();
        const auto type = schema->root()->type();
        // show schema
        std::cout << avro::toString(type) << " " << leaves << std::endl;
        std::cout << schema->toJson() << std::endl;
        auto in = avro::memoryInputStream(buf->data(), buf->size());
        auto decoder = avro::binaryDecoder();
        decoder->init(*in);
        // first bite is int. this is leaf number of schema.
        const auto leaf_idx = decoder->decodeUnionIndex();
        std::cout << "use leaf " << leaf_idx << std::endl;
        // select leaf
        valid_schema_ptr lschema = std::make_shared<valid_schema_ptr::element_type>(schema->root()->leafAt(leaf_idx));
        // show leaf schema
        std::cout << lschema->toJson() << std::endl;
        const avro::GenericRecord gr(lschema->root());
        const std::size_t fcount = gr.fieldCount();
        std::cout << fcount << std::endl;
        for(std::size_t fidx = 0; fidx < fcount; ++fidx) {
          const auto gd = gr.fieldAt(fidx);
          std::cout << fidx << " " <<  gd.type() << " [";
          switch(gd.type()) {
            case avro::AVRO_STRING : {  /*!< String */
              std::cout << decoder->decodeString();
              break;
            }
            case avro::AVRO_BYTES : {  /*!< Sequence of variable length bytes data */
              const auto& bytes = decoder->decodeBytes();
              for( const auto& b : bytes)
                std::cout << b;
              break;
            }
            case avro::AVRO_INT : {  /*!< 32-bit integer */
              std::cout << decoder->decodeInt();
              break;
            }
            case avro::AVRO_LONG : {  /*!< 64-bit integer */
              std::cout << decoder->decodeLong();
              break;
            }
            case avro::AVRO_FLOAT : {  /*!< Floating point number */
              std::cout << decoder->decodeFloat();
              break;
            }
            case avro::AVRO_DOUBLE : {  /*!< Double precision floating point number */
              std::cout << decoder->decodeDouble();
              break;
            }
            case avro::AVRO_BOOL : {  /*!< Boolean value */
              std::cout << decoder->decodeBool();
              break;
            }
            case avro::AVRO_NULL : {  /*!< Null */
              std::cout << "NULL" /*decoder->decodeNull()*/;
              break;
            }
            case avro::AVRO_RECORD : {  /*!< Record, a sequence of fields */
              //std::cout << decoder->
              break;
            }
            case avro::AVRO_ENUM : {  /*!< Enumeration */
              std::cout << decoder->decodeEnum();
              break;
            }
            case avro::AVRO_ARRAY : {  /*!< Homogeneous array of some specific type */
              break;
            }
            case avro::AVRO_MAP : {  /*!< Homogeneous map from string to some specific type */
              break;
            }
            case avro::AVRO_UNION : {  /*!< Union of one or more types */
              break;
            }
            case avro::AVRO_FIXED : {  /*!< Fixed number of bytes */
              break;
            }
            case avro::AVRO_NUM_TYPES : {  /*!< Marker */
              break;
            }
            case avro::AVRO_UNKNOWN : {  /*!< Used internally. */
            }
          }
          std::cout << "]" << std::endl;
        }
      }
    }
    catch(const std::exception& e) {
      std::cout << std::endl << "exception " << e.what() << std::endl;
    }
  }


} /* namespace */

int main(int ac, char* av[]) {
  try {
    std::cout << "test " << __cplusplus << std::endl;
    valid_schema_ptr totalview;

    auto schema = load("./ncdsresources/ControlMessageSchema.avsc");
//    auto schema = load("./schema/QBBO-A-BSX.json");

    std::cout << avro::toString(schema->root()->type()) << " " << schema->root()->leaves() << std::endl;

    std::cout << schema->toJson() << std::endl;

    std::size_t idx = 540;
    buffer_t::value_type max = 0;
    std::istringstream iss;
    std::string str;
    while(auto buf = load("./schema/", idx++, ".sch")) {
      try {
        pbuffer(buf->data(), buf->size());
        auto data = std::make_shared<avro::GenericDatum>(*schema);
        auto in = avro::memoryInputStream(buf->data(), buf->size());
        auto decoder = avro::binaryDecoder();
        decoder->init(*in);
        avro::decode(*decoder, *data);
        const avro::GenericRecord& record = data->value<avro::GenericRecord>();
        for (size_t i = 0; i < record.fieldCount(); i++) {
          avro::GenericDatum datum = record.fieldAt(i);
          std::cout << record.schema()->nameAt(i) << ": ";
          if (datum.type() == avro::AVRO_DOUBLE)
            std::cout << datum.value<double>() << std::endl;
          else if (datum.type() == avro::AVRO_LONG)
            std::cout << datum.value<int64_t>() << std::endl;
          else if (datum.type() == avro::AVRO_INT)
            std::cout << datum.value<int>() << std::endl;
          else if (datum.type() == avro::AVRO_STRING)
            std::cout << datum.value<std::string>() << std::endl;
        }
        if(record.field("name").value<std::string>() == "TOTALVIEW") {
          str = record.field("schema").value<std::string>();
          iss = std::move(std::istringstream(record.field("schema").value<std::string>()));
          break;
        }
      }
      catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
      }
    }
    evidence(str, load("/mnt/data1/butiaev/TOTALVIEW_1/TOTALVIEW.stream_", 0, ".msg"));
#if 0
    std::cout << iss.str() << std::endl;
    if(auto twschema = load(iss)) {
      std::size_t idx = 0;
      std::cout << avro::toString(twschema->root()->type()) << " " << twschema->root()->leaves() << std::endl;
      std::cout << twschema->toJson() << std::endl;
      while(auto buf = load("/mnt/data1/butiaev/TOTALVIEW_1/TOTALVIEW.stream_", idx++, ".msg")) {
        try {
          pbuffer(buf->data(), buf->size());
          auto data = std::make_shared<avro::GenericDatum>(*twschema);
          auto in = avro::memoryInputStream(buf->data(), buf->size());
          auto decoder = avro::binaryDecoder();
          decoder->init(*in);
          avro::decode(*decoder, *data);
          const avro::GenericRecord& record = data->value<avro::GenericRecord>();
          for (size_t i = 0; i < record.fieldCount(); i++) {
            avro::GenericDatum datum = record.fieldAt(i);
            std::cout << record.schema()->nameAt(i) << ": ";
            if (datum.type() == avro::AVRO_DOUBLE)
              std::cout << datum.value<double>() << std::endl;
            else if (datum.type() == avro::AVRO_LONG)
              std::cout << datum.value<int64_t>() << std::endl;
            else if (datum.type() == avro::AVRO_INT)
              std::cout << datum.value<int>() << std::endl;
            else if (datum.type() == avro::AVRO_STRING)
              std::cout << datum.value<std::string>() << std::endl;
          }
          std::cout << std::endl;
        }
        catch(const std::exception& e) {
          std::cout << e.what() << std::endl;
        }
      }

    }
    while(1)
      std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << idx << " " << std::hex << static_cast<int>(max) << std::endl;
#endif
    return 0;
  }
  catch(const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
