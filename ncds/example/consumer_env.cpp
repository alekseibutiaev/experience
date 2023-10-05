//
// Created by Spencer Sortman on 9/23/21.
//
#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <vector>

#include <nlohmann/json.hpp>

#include <avro/Generic.hh>

#include <NCDSClient.h>
#include <AvroDeserializer.h>
#include <print_records.h>

#include <readconfig.h>

#include "env_configs.h"

class read_json_t {
public:
  read_json_t(const nlohmann::json& json)
    : m_json(json) {
  }
  kf::string_try_t operator()(const std::string& val) const {
    return m_json.contains(val) ? kf::string_try_t(m_json[val].template get<std::string>()) : kf::string_try_t();
  }
private:
  const nlohmann::json& m_json;
};

void err(const std::string&) {

}

int main(int ac, char* av[]) {
  try {
    std::ifstream ifs("config.json");
    nlohmann::json j = nlohmann::json::parse(ifs);
    std::cout << j << std::endl;
    read_json_t rj(j);
    tmp.read_config(rj, err);

    kf::config_t tmp;
    std::unique_ptr<RdKafka::Conf> kafka_config = get_kafka_config_env();
    std::unordered_map<std::string, std::string> auth_config = get_auth_config_env();

    int ms_timeout = 10000;

    std::string topic;
    if (const char* env_t = std::getenv("TOPIC"))
      topic = env_t;
    else
      throw std::runtime_error("Environment variable TOPIC not set");

    ncds::NCDSClient ncds_client(kafka_config.get(), auth_config);

    std::unique_ptr<RdKafka::KafkaConsumer> kafka_consumer = ncds_client.NCDSKafkaConsumer(topic);
    std::unique_ptr<RdKafka::Message> msg = std::unique_ptr<RdKafka::Message>(kafka_consumer->consume(ms_timeout));

    if(RdKafka::ERR_NO_ERROR != msg->err())
      std::cout << msg->errstr() << std::endl;

    std::cout << std::string(static_cast<const char*>(msg->payload()), msg->len()) << std::endl;

    pbuffer(msg->payload(), msg->len());
    avro::ValidSchema schema = ncds_client.get_schema(topic);
    ncds::DeserializeMsg deserializer(schema);

    if(msg->payload() != NULL) {
        avro::GenericRecord record = deserializer.deserialize_msg(*msg);
        print_records({record}, get_stream(record.field("name").value<std::string>()));
    }
    else
        std::cout << "Message payload was null" << std::endl;
  }
  catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}