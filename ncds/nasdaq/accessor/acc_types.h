#pragma once

#include <memory>

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

    class avro_record_t : public record_t, public std::pair<std::shared_ptr<avro::GenericRecord>, std::shared_ptr<avro::Decoder>> {
    public:
      using base_type_t = std::pair<std::shared_ptr<avro::GenericRecord>, std::shared_ptr<avro::Decoder>>;
    public:
      using base_type_t::base_type_t;
    };

    using avro_record_ptr = std::shared_ptr<avro_record_t>;

  } /* namespace acc */

} /* namespace nasdaq */


