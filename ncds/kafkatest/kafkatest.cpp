#include <iostream>
#include <fstream>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include <avro/Generic.hh>
#include <avro/ValidSchema.hh>
#include <avro/Compiler.hh>

#include <config.h>

namespace {

  avro::ValidSchema load(const std::string& file) {
    std::ifstream ifs(file.c_str());
    if(!ifs.good())
      throw(std::runtime_error("can`t open file: " + file));
    avro::ValidSchema schema;
    avro::compileJsonSchema(ifs, schema);
    return schema;
  }

  class read_json_t {
  public:
    read_json_t(const nlohmann::json& json)
      : m_json(json) {
    }
    kf::string_try_t operator()(const std::string& val) const {
      return  m_json.contains(val) ? m_json[val].is_string() ?
        kf::string_try_t(m_json[val]) : m_json[val].dump() : kf::string_try_t();
    }
    
  private:
    const nlohmann::json& m_json;
  };

  void err(const std::string& value) {
    std::cout << "configuaryion error: " << value << std::endl;
  }

} /* namespace */

int main(int ac, char* av[]) {
  try {
    std::cout << "test" << std::endl;
    load("/home/butiaev/project/experience/ncds/ncdsresources/cpx.json");
    load("/home/butiaev/project/experience/ncds/ncdsresources/imaginary.json");
    load("/home/butiaev/project/experience/ncds/ncdsresources/ControlMessageSchema.avsc");

    std::ifstream ifs("config.json");
    nlohmann::json j = nlohmann::json::parse(ifs);
    std::cout << j << std::endl;
    read_json_t rj(j);

    kf::config_t tmp;
    tmp.read_config(rj, err);
    kf::config_t tmp1 = tmp.clone(err);
    std::cout << "out" << std::endl;
  }
  catch(const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  return 0;
}
