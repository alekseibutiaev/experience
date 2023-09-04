#include <string>
#include <memory>
#include <fstream>
#include <unordered_map>
#include <ctime>
#include <sstream>

#include <avro/ValidSchema.hh>

#include <librdkafka/rdkafkacpp.h>
#include <librdkafka/rdkafka.h>

#include "internal/Logging.h"
#include "internal/utils/Oauth.h"
#include "internal/utils/KafkaConfigLoader.h"
#include "internal/utils/AuthenticationConfigLoader.h"
#include "internal/utils/SeekToMidnight.h"
#include "internal/utils/TestConfigLoader.h"
#include "consumer/NasdaqKafkaAvroConsumer.h"

// constructor
NasdaqKafkaAvroConsumer::NasdaqKafkaAvroConsumer() {
};

NasdaqKafkaAvroConsumer::NasdaqKafkaAvroConsumer(RdKafka::Conf* kafka_cfg,
    std::unordered_map<std::string, std::string>& security_cfg) : kafka_conf(kafka_cfg) {
  KafkaConfigLoader kafka_config_loader;
  AuthenticationConfigLoader auth_config_loader;

  logger = spdlog::get(LOGGER);

  // If this is not an integration test
  if (kafka_cfg != nullptr) {
    token_cb = std::make_unique<NCDSOAuthBearerTokenRefreshCb>(security_cfg);
    std::string errstr;
    kafka_conf->set("oauthbearer_token_refresh_cb", this->token_cb.get(), errstr);
    kafka_config_loader.validate_and_add_specific_properties(kafka_cfg);
    rd_kafka_conf_set_log_cb(kafka_cfg->c_ptr_global(), logger_cb);
  }
  else {
    test_conf = std::unique_ptr<RdKafka::Conf>(load_kafka_config_for_ncds_test());
    kafka_conf = test_conf.get();
  }

  read_schema_topic.set_kafka_props(kafka_conf);
  read_schema_topic.set_auth_props(security_cfg);
  client_id = auth_config_loader.get_client_id(security_cfg);
}


std::unique_ptr<RdKafka::KafkaConsumer> NasdaqKafkaAvroConsumer::get_kafka_consumer(const std::string &topic_name) {
  std::vector<RdKafka::TopicPartition *> partitions;
  std::unique_ptr<RdKafka::TopicPartition> topic_partition = std::unique_ptr<RdKafka::TopicPartition>(RdKafka::TopicPartition::create(topic_name + ".stream", 0, RdKafka::Topic::OFFSET_END));
  partitions.push_back(topic_partition.get());
  auto kafka_consumer = NasdaqKafkaAvroConsumer::get_consumer(topic_name);
  kafka_consumer->assign(partitions);
  std::string auto_offset_cfg;
  kafka_conf->get(KafkaConfigLoader::AUTO_OFFSET_RESET_CONFIG, auto_offset_cfg);
  if (auto_offset_cfg == "earliest" || auto_offset_cfg == "smallest" || auto_offset_cfg == "beginning")
    seek_to_midnight_at_past_day(kafka_consumer.get(), topic_partition.get(), 0);
  return kafka_consumer;
}

std::unique_ptr<RdKafka::KafkaConsumer> NasdaqKafkaAvroConsumer::get_kafka_consumer(const std::string &topic_name, long timestamp)
{
    std::vector<RdKafka::TopicPartition *> partitions;
	std::unique_ptr<RdKafka::TopicPartition> topic_partition = std::unique_ptr<RdKafka::TopicPartition>(RdKafka::TopicPartition::create(topic_name + ".stream", 0, RdKafka::Topic::OFFSET_END));
	partitions.push_back(topic_partition.get());

	auto kafka_consumer = NasdaqKafkaAvroConsumer::get_consumer(topic_name);

	// seek to a specific timestamp
	topic_partition->set_offset(timestamp);

    kafka_consumer->assign(partitions);

    kafka_consumer->offsetsForTimes(partitions, 5000);

	kafka_consumer->seek(*(topic_partition.get()), 5000);

	return kafka_consumer;
}

avro::ValidSchema NasdaqKafkaAvroConsumer::get_schema(const std::string &topic)
{
    avro::ValidSchema kafka_schema = this->read_schema_topic.read_schema(topic);
	return kafka_schema;
}

std::unique_ptr<RdKafka::KafkaConsumer> NasdaqKafkaAvroConsumer::get_consumer(const std::string &stream_name)
{
	std::string errstr;
	time_t t = time(NULL);
	tm* tPtr = localtime(&t);

	std::string group_id = this->client_id + "_" + stream_name + "_" + std::to_string(tPtr->tm_mday);
	if (this->kafka_conf->set(KafkaConfigLoader::GROUP_ID_CONFIG, group_id.c_str(), errstr) != RdKafka::Conf::CONF_OK) {
	    throw std::runtime_error("Error setting group id: " + errstr);
	}

	auto kafka_consumer = std::unique_ptr<RdKafka::KafkaConsumer>(RdKafka::KafkaConsumer::create(this->kafka_conf, errstr));
    if (!kafka_consumer.get()) {
        throw std::runtime_error("Failed to create consumer: " + errstr);
    }
    return kafka_consumer;
}

std::set<std::string> NasdaqKafkaAvroConsumer::get_topics() {
    return this->read_schema_topic.get_topics();
}

void NasdaqKafkaAvroConsumer::logger_cb (const rd_kafka_t *rk, int level,
                                         const char *fac, const char *buf) {
    std::stringstream ss;
    ss << "RDKAFKA-" << level << "-" << fac << ": " << rd_kafka_name(rk) <<  ": " << buf;
    auto logger = spdlog::get(LOGGER);
    logger->debug("RDKAFKA-{}-{}: {}: {}", level, fac, rd_kafka_name(rk), buf);
}

