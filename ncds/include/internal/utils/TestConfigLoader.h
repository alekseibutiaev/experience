#ifndef TESTCONFIGLOADER_H_
#define TESTCONFIGLOADER_H_
#include <librdkafka/rdkafkacpp.h>
#include <iostream>
#include <unordered_map>

inline RdKafka::Conf* load_test_config() {
    std::string brokers = "<change_me>";
    std::string errstr;

    // create kafka config
    RdKafka::Conf *kafka_conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    kafka_conf->set("debug", "all", errstr);
    std::cerr << "debug: " << errstr << std::endl;
    errstr = "";

    kafka_conf->set("metadata.broker.list", brokers, errstr);
    std::cerr << "metadata.broker.list: " << errstr << std::endl;
    errstr = "";

    kafka_conf->set("security.protocol", "SASL_SSL", errstr);
    std::cerr << "security.protocol: " << errstr << std::endl;
    errstr = "";

    kafka_conf->set("ssl.ca.location", "ncdscert.crt", errstr);
    std::cerr << "ssl.ca.location: " << errstr << std::endl;
    errstr = "";
    kafka_conf->set("sasl.mechanism", "OAUTHBEARER", errstr);
    std::cerr << "sasl.mechanism: " << errstr << std::endl;
    errstr = "";

    kafka_conf->set("sasl.oauthbearer.config", "dummy", errstr);
    std::cerr << "sasl.oauthbearer.config: " << errstr << std::endl;
    errstr = "";

    std::string group_id = "test_group_id";
    kafka_conf->set("group.id", group_id.c_str(), errstr);
    std::cerr << "group.id: " << errstr << std::endl;
    errstr = "";

    kafka_conf->set("auto.offset.reset", "earliest", errstr);
    std::cerr << "auto.offset.reset: " << errstr << std::endl;
    errstr = "";

    return kafka_conf;
}

inline RdKafka::Conf* load_kafka_config_for_ncds_test() {
    RdKafka::Conf *kafka_cfg = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    std::string errstr;
//    kafka_cfg->set("debug", "all", errstr);
    kafka_cfg->set("bootstrap.servers", "localhost:9092", errstr);
    kafka_cfg->set("client.id", "test_consumer_1", errstr);
    kafka_cfg->set("enable.auto.commit", "false", errstr);
    kafka_cfg->set("auto.offset.reset", "earliest", errstr);
    kafka_cfg->set("enable.ssl.certificate.verification", "false", errstr);
    kafka_cfg->set("security.protocol", "plaintext", errstr);
    kafka_cfg->set("sasl.mechanism", "PLAIN", errstr);
    return kafka_cfg;
}

inline std::unordered_map<std::string, std::string> load_test_auth_config() {
    std::unordered_map<std::string, std::string> auth_config = {
            {"oauth.token.endpoint.uri", "<change_me>"},
            {"oauth.client.id", "<change_me>"},
            {"oauth.client.secret", "<change_me>"}
    };
    return auth_config;
}

#endif
