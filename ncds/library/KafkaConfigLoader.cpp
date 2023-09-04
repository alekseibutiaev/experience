#include <cstdio>
#include <memory>

#include <json-c/json.h>

#include "internal/utils/KafkaConfigLoader.h"
#include "internal/utils/TestConfigLoader.h"
#include "internal/utils/FindResources.h"


const std::string KafkaConfigLoader::AUTO_OFFSET_RESET_CONFIG = "auto.offset.reset";
const std::string KafkaConfigLoader::GROUP_ID_CONFIG = "group.id";

//constructor
KafkaConfigLoader::KafkaConfigLoader() {
    this->BOOTSTRAP_SERVERS = "bootstrap.servers";
}

RdKafka::Conf* KafkaConfigLoader::load_config() {
    RdKafka::Conf * cfg;
    cfg = load_test_config();
    KafkaConfigLoader::nasdaq_specific_config(cfg);
    return cfg;
}

void KafkaConfigLoader::nasdaq_specific_config(RdKafka::Conf *p) {
    std::string errstr;
    p->set("security.protocol", "SASL_SSL", errstr);
    p->set("sasl.mechanisms", "OAUTHBEARER", errstr);
    p->set("enable.ssl.certificate.verification", "false", errstr);
}

void KafkaConfigLoader::validate_and_add_specific_properties(RdKafka::Conf *p) {
    std::string value;
    if (p->get(BOOTSTRAP_SERVERS, value) != RdKafka::Conf::CONF_OK) {
        throw std::runtime_error("bootstrap.servers Properties is not set in the Kafka Configuration");
    }
    nasdaq_specific_config(p);
}

int get_timeout_config() {
    FILE *fp;
    char buffer[1024];
    struct json_object *parsed_json;
    struct json_object *timeout_json;

    std::string file_path = get_resource_path() + "consumer-properties.json";
    std::cout << file_path << std::endl;
    try {
        fp = std::fopen(file_path.c_str(),"r");
        fread(buffer, 1024, 1, fp);
        fclose(fp);
    }
    catch (std::exception &e) {
        std::string err_str = e.what();
        throw std::runtime_error("Unable to read from " + file_path + " : " + err_str);
    }

    parsed_json = json_tokener_parse(buffer);

    json_object_object_get_ex(parsed_json, "timeout", &timeout_json);

    int timeout = json_object_get_int(timeout_json);

    json_object_put(parsed_json);

    return timeout;
}