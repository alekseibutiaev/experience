#pragma once

#include <map>
#include <string>
#include <optional>
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

} /* namespace RdKafka */

namespace kf {

  using string_try_t = std::optional<std::string>;
  using parameters_t = std::map<std::string, std::string>;

  using get_property_t = std::function<string_try_t(const std::string&)>;
  using error_t = std::function<void(const std::string&)>;

} /* namespace kf */
