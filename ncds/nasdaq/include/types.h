#pragma once

#include <map>
#include <string>
#include <optional>
#include <functional>

#define __FILE_STR__ [](){ \
  return (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) + std::string(":") + std::to_string(__LINE__) + " ";\
}()

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

} /* namespace RdKafka */

namespace avro {

  class GenericRecord;

} /* namespace avro */

namespace kf {

  using record_ptr = std::shared_ptr<avro::GenericRecord>;

  using string_try_t = std::optional<std::string>;
  using parameters_t = std::map<std::string, std::string>;

  using get_property_t = std::function<string_try_t(const std::string&)>;

} /* namespace kf */
