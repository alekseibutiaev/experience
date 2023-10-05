#pragma once

#include <string>
#include <memory>
#include <vector>
#include <functional>

#include "types.h"

namespace RdKafka {

  class Conf;

} /* namespace RdKafka */

namespace kf {

  enum params_t {
    e_csv,
    e_string,
    e_integer,
    e_boolean
  };

  



  class config_t {
  public:
    using buffer_t = std::vector<unsigned char>;
    using get_property_t = std::function<string_try_t(const std::string&)>;
    using error_t = std::function<void(const std::string&)>;
    using kf_cong_ptr = std::unique_ptr<RdKafka::Conf>;
  public:
    enum type_t {
      e_global,
      e_topic
    };
  public:
    config_t(const config_t::type_t& value = e_global);
    void read_config(const get_property_t& get_property, const error_t& err_notify);
    void set(RdKafka::DeliveryReportCb* value, const error_t& err_notify);
    void set(RdKafka::OAuthBearerTokenRefreshCb* value, const error_t& err_notify);
    void set(RdKafka::EventCb* value, const error_t& err_notify);
    void set(RdKafka::Conf* value, const error_t& err_notify);
    void set(RdKafka::PartitionerCb* value, const error_t& err_notify);
    void set(RdKafka::PartitionerKeyPointerCb* value, const error_t& err_notify);
    void set(RdKafka::SocketCb* value, const error_t& err_notify);
    void set(RdKafka::OpenCb* value, const error_t& err_notify);
    void set(RdKafka::RebalanceCb* value, const error_t& err_notify);
    void set(RdKafka::OffsetCommitCb* value, const error_t& err_notify);
    void set(RdKafka::SslCertificateVerifyCb* value, const error_t& err_notify);
    void set(RdKafka::CertificateType cert_type, RdKafka::CertificateEncoding cert_enc,
      const buffer_t& value, const error_t& err_notify);
    const RdKafka::Conf& get_config() const;
  private:
    using strings_t = std::vector<std::string>;
  private:
    kf_cong_ptr m_config;
    const strings_t& m_param;
  private:
    static const strings_t glogal;
    static const strings_t topic;
  };

//  kf_cong_ptr read_config(const get_property_t& get);



} /* namespace kf */
