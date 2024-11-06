#pragma once

#include <map>
#include <memory>
#include <string>
#include <optional>
#include <chrono>
#include <functional>

namespace RdKafka {

  class Conf;
  class DeliveryReportCb;
  class OAuthBearerTokenRefreshCb;
  class EventCb;
  class Conf;
  class PartitionerCb;
  class PartitionerKeyPointerCb;
  class SocketCb;
  class OpenCb;
  class RebalanceCb;
  class OffsetCommitCb;
  class SslCertificateVerifyCb;
  class TopicPartition;
  class KafkaConsumer;
  class Message;

} /* namespace RdKafka */

namespace avro {

  class GenericRecord;

} /* namespace avro */

namespace kf {

  using record_ptr = std::shared_ptr<avro::GenericRecord>;
  using parameters_t = std::map<std::string, std::string>;
  using clock_t = std::chrono::high_resolution_clock;
  using time_point_t = clock_t::time_point;
  using string_try_t = std::optional<std::string>;
  using get_property_t = std::function<string_try_t(const std::string&)>;

} /* namespace kf */
