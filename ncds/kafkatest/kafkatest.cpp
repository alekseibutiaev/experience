#include <iostream>
#include <fstream>
#include <stdexcept>
#include <thread>

#include <nlohmann/json.hpp>

#include <avro/Generic.hh>
#include <avro/ValidSchema.hh>
#include <avro/Compiler.hh>

#include <config.h>
#include <consumer.h>

// https://github.com/confluentinc/librdkafka/issues/2758

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
    std::cout << "configuration error: " << value << std::endl;
  }

} /* namespace */

int main(int ac, char* av[]) {
  try {
    std::cout << "test" << std::endl;
/*
    const auto sch = load("/home/butiaev/project/experience/ncds/ncdsresources/cpx.json");
    const auto sch = load("/home/butiaev/project/experience/ncds/ncdsresources/imaginary.json");
    const auto sch = load("/home/butiaev/project/experience/ncds/ncdsresources/ControlMessageSchema.avsc");
*/
    const auto sch = load("/home/butiaev/project/experience/ncds/resources/TOTALVIEW.json");

    kf::config_t tmp;
    std::ifstream ifs("config.json");
    nlohmann::json j = nlohmann::json::parse(ifs);
    std::cout << j << std::endl;
    read_json_t rj(j);
    tmp.read_config(rj, err);
    kf::consumer_t consumer(tmp, rj, err);
    consumer.test(sch);
/**/

    for(;;)
      std::this_thread::sleep_for(std::chrono::seconds(1));

    return 0;
/**/
  }
  catch(const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  return 0;
}
