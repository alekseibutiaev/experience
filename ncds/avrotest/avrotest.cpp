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
#include "avro/Compiler.hh"
#include "avro/Encoder.hh"
#include "avro/Decoder.hh"
#include "avro/Specific.hh"


#include <print_records.h>

namespace {

  using pair_t = std::pair<avro::ValidSchema, avro::GenericDatum>;
  using buffer_t = std::vector<unsigned char>;
  using buffer_try_t = std::optional<buffer_t>;
  using valid_schema_ptr = std::shared_ptr<avro::ValidSchema>;


  valid_schema_ptr load(const std::string& file) {
    if(auto ifs = std::ifstream(file.c_str())) {
      std::string error;
      valid_schema_ptr schema = std::make_shared<valid_schema_ptr::element_type>();
      avro::compileJsonSchema(ifs, *schema, error);
      return schema;
    }
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

    auto schema = load("./ncdsresources/ControlMessageSchema.avsc");
//    auto schema = load("./schema/QBBO-A-BSX.json");

    std::cout << avro::toString(schema->root()->type()) << " " << schema->root()->leaves() << std::endl;

    std::cout << schema->toJson() << std::endl;

    std::size_t idx = 0;
    buffer_t::value_type max = 0;
    if(auto buf = load("./schema/", idx++, ".sch")) {
      pbuffer(buf->data(), buf->size());
      auto data = std::make_shared<avro::GenericDatum>(*schema);
      auto in = avro::memoryInputStream(buf->data(), buf->size());
      auto decoder = avro::binaryDecoder();
      decoder->init(*in);
      avro::decode(*decoder, *data);
      const avro::GenericRecord& r = data->value<avro::GenericRecord>();
      std::map<std::string, bool>
      for (size_t i = 0; i < r.fieldCount(); i++) {
        avro::GenericDatum datum = r.fieldAt(i);
        
        std::cout << r.schema()->nameAt(i) << ": ";
        if (datum.type() == avro::AVRO_DOUBLE)
          std::cout << datum.value<double>() << std::endl;
        else if (datum.type() == avro::AVRO_LONG)
          std::cout << datum.value<int64_t>() << std::endl;
        else if (datum.type() == avro::AVRO_INT)
          std::cout << datum.value<int>() << std::endl;
        else if (datum.type() == avro::AVRO_STRING)
          std::cout << datum.value<std::string>() << std::endl;
      }


    }

#if 0

//    while(const auto buf = load("/mnt/data1/butiaev/QBBO-A-BSX/QBBO-A-BSX.stream_", idx++, ".msg")) {
    while(auto buf = load("./schema/", idx++, ".sch")) {
      pbuffer(buf->data(), buf->size());
      avro::GenericDatum data(schema);
      auto in = avro::memoryInputStream(buf->data(), buf->size());
      auto decoder = avro::binaryDecoder();
      decoder->init(*in);
      avro::decode(*decoder, data);
/*
      const avro::GenericRecord& r = data.value<avro::GenericRecord>();
      for (size_t i = 0; i < r.fieldCount(); i++) {
        avro::GenericDatum datum = r.fieldAt(i);
        std::cout << r.schema()->nameAt(i) << ": ";
        if (datum.type() == avro::AVRO_DOUBLE)
          std::cout << datum.value<double>() << std::endl;
        else if (datum.type() == avro::AVRO_LONG)
          std::cout << datum.value<int64_t>() << std::endl;
        else if (datum.type() == avro::AVRO_INT)
          std::cout << datum.value<int>() << std::endl;
        else if (datum.type() == avro::AVRO_STRING)
          std::cout << datum.value<std::string>() << std::endl;
      }
*/
    }
#endif
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
