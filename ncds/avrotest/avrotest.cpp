#include <fstream>
#include <iostream>
#include <optional>
#include <iterator>
#include <vector>

#include <avro/Generic.hh>
#include <avro/ValidSchema.hh>
#include <avro/Compiler.hh>

#include "avro/Compiler.hh"
#include "avro/Encoder.hh"
#include "avro/Decoder.hh"
#include "avro/Specific.hh"


#include <print_records.h>

namespace {

  using buffer_t = std::vector<unsigned char>;
  using buffer_try_t = std::optional<buffer_t>;

  avro::ValidSchema load(const std::string& file) {
    std::ifstream ifs(file.c_str());
    if(!ifs.good())
      throw(std::runtime_error("can`t open file: " + file));
    std::string error;
    avro::ValidSchema schema;
    avro::compileJsonSchema(ifs, schema, error);
    return schema;
  }

  buffer_try_t load(std::size_t idx) {
    buffer_try_t res;
    std::ifstream ifs("./text/buf_" + std::to_string(idx) + ".text");
    if(ifs)
      res = buffer_t(std::istream_iterator<buffer_t::value_type>(ifs), std::istream_iterator<buffer_t::value_type>());
    return res;
  }

} /* namespace */

int main(int ac, char* av[]) {
  try {
    std::cout << "test" << std::endl;

    auto schema = load("./ncdsresources/schema.json");

    std::cout << schema.toJson() << std::endl;
    std::size_t idx = 0;
    while(const auto buf = load(idx++)) {
      pbuffer(buf->data(), buf->size());
      auto is = avro::memoryInputStream(buf->data(), buf->size());
      auto d = avro::binaryDecoder();
      d->init(*is);
      avro::GenericDatum datum(schema);
      avro::decode(*d, datum);
      std::cout << datum.type() << std::endl;

    }
    std::cout << idx << std::endl;
    return 0;
  }
  catch(const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  return 0;
}
