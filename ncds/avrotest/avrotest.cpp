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
          iss = std::move(std::istringstream(record.field("schema").value<std::string>()));
          break;
        }
      }
      catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
      }
    }
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
    return 0;
  }
  catch(const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
