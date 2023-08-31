#include <librdkafka/rdkafkacpp.h>

#include "env_configs.h"

std::unique_ptr<RdKafka::Conf> get_kafka_config() {
    std::string brokers;
    if (const char* env_b = std::getenv("BROKERS")) {
        brokers = env_b;
    }
    else {
        throw std::runtime_error("Environment variable BROKERS not set");
    }

    std::string errstr;

    // Kafka Configs
    std::unique_ptr<RdKafka::Conf> kafka_conf = std::unique_ptr<RdKafka::Conf>(RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL));
    kafka_conf->set("debug", "all", errstr);
    kafka_conf->set("metadata.broker.list", brokers, errstr);

    if (const char* env_ssl = std::getenv("SSL_CA_LOCATION")) {
        kafka_conf->set("ssl.ca.location", env_ssl, errstr);
    }

    kafka_conf->set("ssl.ca.location", "ncdscert.crt", errstr);
    kafka_conf->set("group.id", "test_group_id", errstr);
    kafka_conf->set("auto.offset.reset", "earliest", errstr);

    return kafka_conf;
}

std::unordered_map<std::string, std::string> get_auth_config() {
    // TODO: Update the authentication configurations
    const char* env_endpt = std::getenv("TOKEN_ENDPOINT");
    const char* env_id = std::getenv("CLIENT_ID");
    const char* env_secret = std::getenv("CLIENT_SECRET");
    if (!env_endpt || !env_id || !env_secret) {
        throw std::runtime_error("Set environment variables TOKEN_ENDPOINT, CLIENT_ID, and CLIENT_SECRET");
    }
    std::string token_endpoint = env_endpt;
    std::string client_id = env_id;
    std::string client_secret = env_secret;

    std::unordered_map<std::string, std::string> auth_config = {
            {"oauth.token.endpoint.uri", token_endpoint},
            {"oauth.client.id", client_id},
            {"oauth.client.secret", client_secret}};

    return auth_config;
}
