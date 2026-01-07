#pragma once

#include <string>
#include <memory>
#include <vector>
#include <functional>

#include "acc_types.h"

namespace nasdaq {

  class error_t;

  namespace acc {

    class config_t {
    public:
      using buffer_t = std::vector<unsigned char>;
    public:
      enum type_t {
        e_global,
        e_topic
      };
    public:
      config_t(const config_t::type_t& type = e_global);
      config_t(const get_property_t& get_property, const error_t& error, const config_t::type_t& type = e_global);
      config_t clone(const error_t& error) const;
      void read_config(const get_property_t& get_property, const error_t& error);

      void set(const std::string& name, RdKafka::Conf* value, const error_t& error);
      void set(RdKafka::ConsumeCb* value, const error_t& error);

      void set(RdKafka::DeliveryReportCb* value, const error_t& erroror);
      void set(RdKafka::OAuthBearerTokenRefreshCb* value, const error_t& error);
      void set(RdKafka::EventCb* value, const error_t& error);
      void set(RdKafka::PartitionerCb* value, const error_t& error);
      void set(RdKafka::PartitionerKeyPointerCb* value, const error_t& error);
      void set(RdKafka::SocketCb* value, const error_t& error);
      void set(RdKafka::OpenCb* value, const error_t& error);
      void set(RdKafka::RebalanceCb* value, const error_t& error);
      void set(RdKafka::OffsetCommitCb* value, const error_t& error);
      void set(RdKafka::SslCertificateVerifyCb* value, const error_t& error);

      RdKafka::DeliveryReportCb* get(RdKafka::DeliveryReportCb* value, const error_t& error);
      RdKafka::OAuthBearerTokenRefreshCb* get(RdKafka::OAuthBearerTokenRefreshCb* value, const error_t& error);
      RdKafka::EventCb* get(RdKafka::EventCb* value, const error_t& error);
      RdKafka::PartitionerCb* get(RdKafka::PartitionerCb* value, const error_t& error);
      RdKafka::PartitionerKeyPointerCb* get(RdKafka::PartitionerKeyPointerCb* value, const error_t& error);
      RdKafka::SocketCb* get(RdKafka::SocketCb* value, const error_t& error);
      RdKafka::OpenCb* get(RdKafka::OpenCb* value, const error_t& error);
      RdKafka::RebalanceCb* get(RdKafka::RebalanceCb* value, const error_t& error);
      RdKafka::OffsetCommitCb* get(RdKafka::OffsetCommitCb* value, const error_t& error);
      RdKafka::SslCertificateVerifyCb* get(RdKafka::SslCertificateVerifyCb* value, const error_t& error);
      
      void get(const std::string&, std::string& value, const error_t& error);
      void set(const std::string&, const std::string& value, const error_t& error);

      RdKafka::Conf* get_config() const;
      const config_t::type_t& get_type() const;
      void print() const;
    private:
      using strings_t = std::vector<std::string>;
      using cong_ptr = std::shared_ptr<RdKafka::Conf>;
    private:
      static config_t::strings_t available_parameters();
    private:
      const config_t::type_t m_type;
      cong_ptr m_config;
    private:
      static const strings_t param;
    };

  } /* namespace acc */

} /* namespace nasdaq */
