#include <iostream>
#include <string>
#include <tuple>
#include <memory>

#include <librdkafka/rdkafkacpp.h>

#include <avro/ValidSchema.hh>
#include <avro/Generic.hh>

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/spdlog.h>

#include "consumer/NasdaqKafkaAvroConsumer.h"
#include "internal/utils/AuthenticationConfigLoader.h"
#include "internal/utils/KafkaConfigLoader.h"
#include "internal/Logging.h"

#include "AvroDeserializer.h"
#include "NCDSClient.h"

namespace ncds {

  NCDSClient::NCDSClient(RdKafka::Conf *kafka_cfg, std::unordered_map<std::string, std::string> &security_cfg) {
    auto config_map = get_logger_configs();

    this->timeout = get_timeout_config();

    try {
      int max_size = config_map["max_size"];
      int max_files = config_map["max_files"];

      this->logger = spdlog::rotating_logger_mt("logger", "logfile", max_size, max_files);
      int debug = config_map["debug"];
      if (debug) {
          logger->set_level(spdlog::level::debug);
      } else {
          logger->set_level(spdlog::level::info);
      }
      logger->debug("Making NCDS Client ...");
    }
    catch (spdlog::spdlog_ex) {
      this->logger = spdlog::get(LOGGER);
    }

    this->nasdaq_kafka_avro_consumer = NasdaqKafkaAvroConsumer(kafka_cfg, security_cfg);

    try {
      AuthenticationConfigLoader auth_config_loader = AuthenticationConfigLoader();
      if (!security_cfg.empty()) {
        logger->debug("security cfg not empty ...");
        if (auth_config_loader.validate_security_config(security_cfg)) {
            this->nasdaq_kafka_avro_consumer = NasdaqKafkaAvroConsumer(kafka_cfg, security_cfg);
        }
      } else {
        throw std::runtime_error("Authentication Config is missing");
      }
    }
    catch (...) {
      throw std::runtime_error("Authentication Config is missing");
    }
  }

  std::set<std::string> NCDSClient::list_topics_for_the_client() {
    std::set<std::string> topics = nasdaq_kafka_avro_consumer.get_topics();
    return topics;
  }

  avro::ValidSchema NCDSClient::get_schema(const std::string &topic) {
    avro::ValidSchema kafka_schema = nasdaq_kafka_avro_consumer.get_schema(topic);
//    originally returns a string but we're changing to to return a schema object for now
    return kafka_schema;
  }

  std::unique_ptr<RdKafka::KafkaConsumer> NCDSClient::NCDSKafkaConsumer(const std::string &topic) {
    return nasdaq_kafka_avro_consumer.get_kafka_consumer(topic);
  }

  std::unique_ptr<RdKafka::KafkaConsumer> NCDSClient::NCDSKafkaConsumer(const std::string &topic, long timestamp) {
    return nasdaq_kafka_avro_consumer.get_kafka_consumer(topic, timestamp);
  }

  std::vector<avro::GenericRecord> NCDSClient::top_messages(const std::string &topic_name, int num_messages) {
    int ms = this->timeout; //milliseconds
    std::unique_ptr<RdKafka::KafkaConsumer> kafka_consumer = NCDSClient::NCDSKafkaConsumer(topic_name);

    logger->debug("created kafka consumer");
    std::vector<avro::GenericRecord> messages;
    logger->debug("created message vector");

    for (int i = 0; i < num_messages; i++) {
      std::unique_ptr<RdKafka::Message> message = std::unique_ptr<RdKafka::Message>(kafka_consumer->consume(ms));
      if (message->payload() == NULL || NCDSClient::end_of_data(kafka_consumer.get(), topic_name)) {
        std::cout << "--------------------------------END of Stream--------------------------------";
        break;
      }
      avro::ValidSchema schema = NCDSClient::get_schema(topic_name);
      DeserializeMsg consume(schema);
      avro::GenericRecord msg = consume.deserialize_msg(*message);

      logger->debug("consumed message");
      messages.push_back(msg);
    }

    kafka_consumer->close();
    return messages;
  }

  std::vector<avro::GenericRecord> NCDSClient::top_messages(const std::string &topic_name, long timestamp, int num_messages) {
    int ms = timeout; //milliseconds
    std::unique_ptr<RdKafka::KafkaConsumer> kafka_consumer = NCDSClient::NCDSKafkaConsumer(topic_name, timestamp);
    std::vector<avro::GenericRecord> messages;

    for (int i = 0; i < num_messages; i++) {
      std::unique_ptr<RdKafka::Message> message = std::unique_ptr<RdKafka::Message>(kafka_consumer->consume(ms));
      if (message->payload() == NULL || NCDSClient::end_of_data(kafka_consumer.get(), topic_name)) {
        std::cout << "--------------------------------END of Stream--------------------------------";
        break;
      }
      avro::ValidSchema schema = NCDSClient::get_schema(topic_name);
      DeserializeMsg consume(schema);
      avro::GenericRecord msg = consume.deserialize_msg(*message);
      messages.push_back(msg);
    }
    kafka_consumer->close();
    return messages;
  }

  avro::GenericRecord NCDSClient::get_sample_messages(const std::string &topic_name, const std::string &message_name, bool all_messages) {

    std::unique_ptr<RdKafka::KafkaConsumer> kafka_consumer = NCDSClient::NCDSKafkaConsumer(topic_name);

    int ms = this->timeout;
    avro::ValidSchema schema = NCDSClient::get_schema(topic_name);
    DeserializeMsg consume(schema);
    std::unique_ptr<RdKafka::Message> message = std::unique_ptr<RdKafka::Message>(kafka_consumer->consume(ms));

    if (message->payload() == NULL || NCDSClient::end_of_data(kafka_consumer.get(), topic_name)) {
      throw std::runtime_error("Message is null!");
    }
    avro::GenericRecord sample_msg = consume.deserialize_msg(*message);

    while (true) {
      if (message->payload() == NULL || NCDSClient::end_of_data(kafka_consumer.get(), topic_name)) {
        std::cout << "--------------------------------END of Stream--------------------------------";
        break;
      }
      sample_msg = consume.deserialize_msg(*message);
      if (message_name == sample_msg.schema()->name().simpleName()) {
        std::cout << sample_msg.schema()->name().simpleName() << std::endl;
        for (size_t i = 0; i < sample_msg.fieldCount(); i++) {
          avro::GenericDatum datum = sample_msg.fieldAt(i);
          std::cout << sample_msg.schema()->nameAt(i) << ": ";

          if (datum.type() == avro::AVRO_DOUBLE) {
            double num = datum.value<double>();
            std::cout << num << std::endl;
          } else if (datum.type() == avro::AVRO_LONG) {
            int64_t num = datum.value<int64_t>();
            std::cout << num << std::endl;
          } else if (datum.type() == avro::AVRO_INT) {
            int num = datum.value<int>();
            std::cout << num << std::endl;
          } else if (datum.type() == avro::AVRO_STRING) {
            std::string str = datum.value<std::string>();
            std::cout << str << std::endl;
          }
        }
        if (!all_messages) {
          break;
        }
      }
      message = std::unique_ptr<RdKafka::Message>(kafka_consumer->consume(ms));
    }
    kafka_consumer->close();

    if (!all_messages && message_name != sample_msg.schema()->name().simpleName()) {
        throw std::runtime_error("No consumed message matches the given message name.");
    }
    return sample_msg;

  }

  bool NCDSClient::end_of_data(RdKafka::KafkaConsumer *consumer, const std::string &topic_name) {
    std::vector<RdKafka::TopicPartition *> topic_partitions;
    std::unique_ptr<RdKafka::TopicPartition> topic_partition = std::unique_ptr<RdKafka::TopicPartition>(
            RdKafka::TopicPartition::create(topic_name + ".stream", 0));
    topic_partitions.push_back(topic_partition.get());
    consumer->assignment(topic_partitions);
    consumer->position(topic_partitions);

    for (int i = 0; i < topic_partitions.size(); i++) {
      RdKafka::TopicPartition *position = topic_partitions[i];
      if (position->offset() != RdKafka::Topic::OFFSET_END) {
        return false;
      }
    }
    return true;
  }
}
