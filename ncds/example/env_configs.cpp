#include <iostream>
#include <stdexcept>

#include <utility>
#include <algorithm>
#include <vector>

#include <librdkafka/rdkafkacpp.h>

#include "env_configs.h"

using param_t = std::pair<const char*, const char*>;
using params_t = std::vector<param_t>;

const params_t kafka_params = {
  {"BROKERS", "metadata.broker.list"},
  {"SSL_CA_LOCATION", "ssl.ca.location"},
  {"SSL_CERTIFICATE_LOCATION", "ssl.certificate.location"},
  {"GROUP_ID", "group.id"},
  {"AUTO_OFFSET_RESET", "auto.offset.reset"},
};

const params_t oauth_params = {
  {"OAUTH_TOKEN_ENDPOINT_URI", "oauth.token.endpoint.uri"},
  {"OAUTH_CLIENT_ID", "oauth.client.id"},
  {"OAUTH_CLIENT_SECRET", "oauth.client.secret"},
};


std::unique_ptr<RdKafka::Conf> get_kafka_config_env() {
  if(std::unique_ptr<RdKafka::Conf> kafka_conf = std::unique_ptr<RdKafka::Conf>(RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL))) {
    std::string errstr;
    for(const auto& it : kafka_params) {
      if(const char* value = std::getenv(it.first))
        kafka_conf->set(it.second, value, errstr);
      else
        std::cout << "environment variable " << it.first << " not set" << std::endl;
    }
    // Kafka Configs
    kafka_conf->set("debug", "all", errstr);
    return kafka_conf;
  }
  throw(std::runtime_error("can`t create kafka config"));
}

std::unordered_map<std::string, std::string> get_auth_config_env() {
  std::unordered_map<std::string, std::string> auth_config;
  std::string errstr;
  for(const auto& it : oauth_params) {
    if(const char* value = std::getenv(it.first))
      auth_config[it.second] = value;
    else
      throw(std::runtime_error(std::string("environment variable ") + it.first + " not set" ));
  }
  return auth_config;
}
