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
#include <avro/Types.hh>
#include <avro/GenericDatum.hh>



namespace {

  using buffer_t = std::vector<unsigned char>;
  using buffer_try_t = std::optional<buffer_t>;
  using valid_schema_ptr = std::shared_ptr<avro::ValidSchema>;

  valid_schema_ptr load_schema(std::istream& is) {
    std::string error;
    valid_schema_ptr schema = std::make_shared<valid_schema_ptr::element_type>();
    if(!avro::compileJsonSchema(is, *schema, error))
      std::cout << error << std::endl;
    return schema;
  }

  valid_schema_ptr load_schema(const std::string& file) {
    if(auto ifs = std::ifstream(file.c_str()))
      return load_schema(ifs);
    throw(std::runtime_error("can`t open file: " + file));
  }

  buffer_try_t load(const std::string& prefix, std::size_t idx, const std::string& suffix) {
    std::ostringstream oss;
    oss << prefix << std::setfill('0') << std::setw(8) << idx << suffix;
    const std::string& name = oss.str();
    buffer_try_t res;
    if(auto ifs = std::ifstream(oss.str(), std::ios::binary)) {
      ifs.seekg(0, std::ios_base::end);
      std::size_t s = ifs.tellg();
      ifs.seekg(0, std::ios_base::beg);
      auto buf = buffer_t(s);
      ifs.read(reinterpret_cast<char*>(buf.data()), s);
      res = buf;
    }
    return res;
  }

  void pbuffer(const void* buf, const std::size_t& size) {
    char hex[128] = {0};
    char ch[17] = {0};
    for(std::size_t i = 0; i < size; ++i) {
      sprintf(&hex[(i % 16) * 5], "0x%02X ", reinterpret_cast<const unsigned char*>(buf)[i]);
      sprintf(&ch[(i % 16)], "%c", std::isprint(reinterpret_cast<const unsigned char*>(buf)[i]) ?
        reinterpret_cast<const unsigned char*>(buf)[i] : '.');
      if(0 == (i + 1) % 16)
        std::cout << hex << ch << std::endl;
    }
    if(size % 16)
      std::cout << hex << ch << std::endl;
  }

  void print_records(const std::vector<avro::GenericRecord>& records, std::ostream& os) {
    for (auto &record : records) {
      os << "Message name: " << record.schema()->name().simpleName() << std::endl;
      for (size_t i = 0; i < record.fieldCount(); i++) {
        avro::GenericDatum datum = record.fieldAt(i);
        os << record.schema()->nameAt(i) << ": ";
        if (datum.type() == avro::AVRO_DOUBLE)
          os << datum.value<double>() << std::endl;
        else if (datum.type() == avro::AVRO_LONG)
          os << datum.value<int64_t>() << std::endl;
        else if (datum.type() == avro::AVRO_INT)
          os << datum.value<int>() << std::endl;
        else if (datum.type() == avro::AVRO_STRING)
          os << datum.value<std::string>() << std::endl;
      }
    }
  }

  void evidence(const std::string& str, const buffer_try_t& buf) {
    if(!buf)
      return;
    // show buffer
    try {
      if(const auto& schema = load_schema(str)) {
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
        const avro::NodePtr& np = lschema->root();
        std::cout << np->type() << std::endl;
        std::cout << np->name().fullname() << std::endl;
        std::cout << np->name().ns() << std::endl;
        std::cout << np->name().simpleName() << std::endl;
        std::cout << np->leaves() << std::endl;

        const avro::GenericRecord gr(lschema->root());
        const std::size_t fcount = gr.fieldCount();
        std::cout << "field count: " << fcount << std::endl;
        pbuffer(buf->data(), buf->size());
        for(std::size_t fidx = 0; fidx < fcount; ++fidx) {
          const auto gd = gr.fieldAt(fidx);
          std::cout << fidx << " name: " << np->nameAt(fidx) << " " <<  gd.type() << " [";
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

#if 0
const std::string sch = "./resources/ControlMessageSchema.avsc";
const std::string msgb = "/home/butiaev/project/ncds/schema_out/schema_";
const std::string msge = ".sch";
#else
const std::string sch = "./resources/TOTALVIEW.json";
const std::string msgb = "/mnt/data/butiaev/TOTALVIEW/TOTALVIEW.stream_";
const std::string msge = ".msg";
#endif

int main(int ac, char* av[]) {
  try {
    std::cout << "test " << __cplusplus << std::endl;
    valid_schema_ptr schema = load_schema(sch);
    std::cout << avro::toString(schema->root()->type()) << " " << schema->root()->leaves() << std::endl;
    std::cout << schema->toJson() << std::endl;
    std::size_t idx = 0;
    while(buffer_try_t buf = load(msgb, idx++, msge)) {
      // show schema
      pbuffer(buf->data(), buf->size());
      auto data = std::make_shared<avro::GenericDatum>(*schema);
      auto in = avro::memoryInputStream(buf->data(), buf->size());
      auto decoder = avro::binaryDecoder();
      decoder->init(*in);
      avro::decode(*decoder, *data);
      std::cout << data->type() << std::endl;
      auto r = data->value<avro::GenericRecord>();

  //    std::vector<avro::GenericRecord> records;
  //    records.push_back(*data);
      print_records({r}, std::cout);
    }
    std::cout << "tested: " << idx << " records" << std::endl;
  }
  catch(const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
