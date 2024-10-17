#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <stdexcept>
#include <functional>

#include <nlohmann/json.hpp>

#include "config.h"
#include "avro_decode.h"
#include "consumer.h"
#include "tools.h"

// https://github.com/confluentinc/librdkafka/issues/2758

namespace {

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

  class deletate_t : public kf::avro_decode_t::delegate_t {
  private:
    void begin_msg(const std::string& topic, const std::string& msg) override {
      std::cout << "topic: " << topic << ", message: " << msg;
    }
    void end_msg() override {
      std::cout << std::endl;
    }
    void data(const std::string& field, const std::string& data) override {
      std::cout << ", " << field << ": " << data;
    }
    void data(const std::string& field, const unsigned char& data) override  {
      std::cout << ", " << field << ": " << data;
    }
    void data(const std::string& field, const int& data) override  {
      std::cout << ", " << field << ": " << data;
    }
    void data(const std::string& field, const long& data) override  {
      std::cout << ", " << field << ": " << data;
    }
    void data(const std::string& field, const float& data) override  {
      std::cout << ", " << field << ": " << data;
    }
    void data(const std::string& field, const double& data) override  {
      std::cout << ", " << field << ": " << data;
    }
    void data(const std::string& field, const bool& data) override  {
      std::cout << " " << field << ": " << data;
    }
  };

} /* namespace */

int main(int ac, char* av[]) {
  try {
    std::cout << "test" << std::endl;
    std::ifstream ifs("config.json");
    nlohmann::json j = nlohmann::json::parse(ifs);
    std::cout << j << std::endl;
    std::vector<std::string> topics = {kf::avro_decode_t::control};
    topics.insert(topics.end(), j["topics"].begin(), j["topics"].end());

    deletate_t d;

    read_json_t rj(j);
    kf::config_t cnf;
    cnf.read_config(rj, err);
    kf::consumer_t consumer(cnf, rj, err);
    const std::string cms = j["control_message_schema"];
    kf::avro_decode_t decode(d, cms);
    consumer.consume(topics, decode);
    for(;;)
      std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
  }
  catch(const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  return 0;
}
