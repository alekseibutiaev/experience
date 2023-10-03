#ifndef NCDS_SDK_READSCHEMATOPIC_H
#define NCDS_SDK_READSCHEMATOPIC_H
#include <string>
#include <set>
#include <memory>
#include <librdkafka/rdkafkacpp.h>
#include <avro/ValidSchema.hh>
#include <avro/GenericDatum.hh>
#include <unordered_map>
#include <spdlog/spdlog.h>

/**
 * \defgroup internal internal
 * Internal classes and functions for the Nasdaq Cloud Data Service C++ SDK.
 * @{
 */


/**
 * @brief Class to retrieve the Kafka Schema for the given Topic/Stream.
 */
class ReadSchemaTopic {
public:
  ReadSchemaTopic();
  avro::ValidSchema read_schema(const std::string &topic);
  void set_kafka_props(RdKafka::Conf* props);
  void set_auth_props(std::unordered_map<std::string, std::string> &props);
  std::set<std::string> get_topics();
  //std::string resource_dir;
public:
  int timeout;
private:
  std::string control_schema_name;
  RdKafka::Conf* kafka_props;
  std::unordered_map<std::string, std::string> auth_props;
  std::unique_ptr<RdKafka::KafkaConsumer> get_consumer(const std::string &client_id);
  avro::ValidSchema resource_schema(const std::string &topic);
  std::shared_ptr<spdlog::logger> logger;
};


/**@}*/
#endif //NCDS_SDK_READSCHEMATOPIC_H
