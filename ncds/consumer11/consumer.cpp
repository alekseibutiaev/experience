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
#include <avro/ValidSchema.hh>
#include <avro/Compiler.hh>


#include <AvroDeserializer.h>

#include "env_configs.h"

namespace {

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



} /* namespace */


int main(int ac, char* av[]) {
  try {
    std::unique_ptr<RdKafka::Conf> kafka_config = get_kafka_config_env();
    std::unordered_map<std::string, std::string> auth_config = get_auth_config_env();

    int ms_timeout = 10000;

    std::string topic;
    if (const char* env_t = std::getenv("TOPIC"))
      topic = env_t;
    else
      throw std::runtime_error("Environment variable TOPIC not set");



/*
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
      print_records({record}, *get_stream(record.field("name").value<std::string>()));
    }
    else
      std::cout << "Message payload was null" << std::endl;
*/
  }
  catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}