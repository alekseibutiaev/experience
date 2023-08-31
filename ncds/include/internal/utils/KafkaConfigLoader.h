#ifndef KAFKACONFIGLOADER_H
#define KAFKACONFIGLOADER_H

#include <iostream>
#include <unordered_map>
#include <memory>
#include <librdkafka/rdkafkacpp.h>


/**
 * @ingroup utils
 * @brief Utility to load the kafka configuration parameters.
 */
class KafkaConfigLoader
{
private:
    static void nasdaq_specific_config(RdKafka::Conf *p);

public:
    KafkaConfigLoader();
    std::string BOOTSTRAP_SERVERS;
    static RdKafka::Conf *load_config();
    void validate_and_add_specific_properties(RdKafka::Conf *p);
    const static std::string AUTO_OFFSET_RESET_CONFIG;
    const static std::string GROUP_ID_CONFIG;
};

int get_timeout_config();

#endif