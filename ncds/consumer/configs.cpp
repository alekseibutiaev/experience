#include <librdkafka/rdkafkacpp.h>

#include "configs.h"

std::unique_ptr<RdKafka::Conf> get_kafka_config() {
  // TODO: Update to your broker(s)
  std::string brokers = "<brokers>";
  std::string errstr;

  // Kafka Configs
  std::unique_ptr<RdKafka::Conf> kafka_conf = std::unique_ptr<RdKafka::Conf>(RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL));
  kafka_conf->set("debug", "all", errstr);
  kafka_conf->set("metadata.broker.list", brokers, errstr);

  // TODO: Include the path to the certificate file
  kafka_conf->set("ssl.ca.location", "/path/to/file.crt", errstr);
  kafka_conf->set("group.id", "test_group_id", errstr);
  kafka_conf->set("auto.offset.reset", "earliest", errstr);

  return kafka_conf;
}

std::unordered_map<std::string, std::string> get_auth_config() {
  // TODO: Update the authentication configurations
  std::unordered_map<std::string, std::string> auth_config = {
          {"oauth.token.endpoint.uri", "<endpoint_uri>"},
          {"oauth.client.id", "<client_id>"},
          {"oauth.client.secret", "<client_secret>"}};

  return auth_config;
}
