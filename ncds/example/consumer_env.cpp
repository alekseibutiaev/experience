//
// Created by Spencer Sortman on 9/23/21.
//
#include <iostream>
#include <string>
#include <memory>
#include <vector>

#include <avro/Generic.hh>

#include <printbuf.h>
#include <NCDSClient.h>
#include <AvroDeserializer.h>

#include "print_records.h"
#include "env_configs.h"

int main(int ac, char* av[]) {
  try {
    std::unique_ptr<RdKafka::Conf> kafka_config = get_kafka_config_env();
    std::unordered_map<std::string, std::string> auth_config = get_auth_config_env();

    int ms_timeout = 10000;

    std::string topic;
    if (const char* env_t = std::getenv("TOPIC")) {
        topic = env_t;
    }
    else {
        throw std::runtime_error("Environment variable TOPIC not set");
    }

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
        std::vector<avro::GenericRecord> v = {record};
        print_records(v);
    }
    else {
        std::cout << "Message payload was null" << std::endl;
    }
  }
  catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
}