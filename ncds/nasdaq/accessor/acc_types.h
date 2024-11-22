#pragma once

#include <map>
#include <chrono>
#include <memory>
#include <string>
#include <utility>
#include <optional>
#include <functional>

#include "../types.h"

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
  class ConsumeCb;

  class TopicPartition;
  class KafkaConsumer;
  class Message;

} /* namespace RdKafka */

namespace avro {

  class GenericRecord;
  class Decoder;

} /* namespace avro */

namespace nasdaq {

  namespace acc {

    using record_t = std::pair<std::shared_ptr<avro::GenericRecord>, std::shared_ptr<avro::Decoder>>;
    using parameters_t = std::map<std::string, std::string>;
    using get_property_t = std::function<string_try_t(const std::string&)>;

  } /* namespace acc */

} /* namespace nasdaq */


