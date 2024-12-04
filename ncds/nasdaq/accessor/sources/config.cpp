#include <stdio.h>

#include <cctype>
#include <cstring>

#include <tuple>
#include <iostream>
#include <utility>

#include <librdkafka/rdkafka.h>
#include <librdkafka/rdkafkacpp.h>

#include "error.h"
#include "location.h"
#include "accessor/config.h"

namespace {

  template <typename type_t, typename tuple_t>
  struct index_t;

  template <typename type_t, typename... types_t>
  struct index_t<type_t, std::tuple<type_t, types_t...>> {
      static const std::size_t value = 0;
  };

  template <typename type_t, typename u_t, typename... types_t>
  struct index_t<type_t, std::tuple<u_t, types_t...>> {
      static const std::size_t value = 1 + index_t<type_t, std::tuple<types_t...>>::value;
  };

  static const auto calbacks = std::make_tuple(
    std::pair<RdKafka::DeliveryReportCb*, std::string>(0, "dr_cb"),
    std::pair<RdKafka::OAuthBearerTokenRefreshCb*, std::string>(0, "oauthbearer_token_refresh_cb"),
    std::pair<RdKafka::EventCb*, std::string>(0, "event_cb"),
    std::pair<RdKafka::PartitionerCb*, std::string>(0, "partitioner_cb"),
    std::pair<RdKafka::PartitionerKeyPointerCb*, std::string>(0, "partitioner_key_pointer_cb"),
    std::pair<RdKafka::SocketCb*, std::string>(0, "socket_cb"),
    std::pair<RdKafka::OpenCb*, std::string>(0, "open_cb"),
    std::pair<RdKafka::RebalanceCb*, std::string>(0, "rebalance_cb"),
    std::pair<RdKafka::OffsetCommitCb*, std::string>(0, "offset_commit_cb"),
    std::pair<RdKafka::SslCertificateVerifyCb*, std::string>(0, "ssl_cert_verify_cb")
  );

  static const auto param_ptr = std::tuple_cat(calbacks,
    std::make_tuple(std::pair<RdKafka::Conf*, std::string>(0, "default_topic_conf")));

  template <typename param_t>
  static const std::string& get_name(param_t*) {
    return std::get<std::pair<param_t*, std::string>>(param_ptr).second;
  }

  template<typename first_t, typename second_t>
  void copy(const std::pair<first_t, second_t>& param, const RdKafka::Conf& from, RdKafka::Conf& to,
      const nasdaq::error_t& error) {
    std::string err;
    first_t ptr;
    if(RdKafka::Conf::CONF_OK != from.get(ptr) || RdKafka::Conf::CONF_OK != to.set(param.second, ptr, err))
      error.error(err);
  }

  template <typename... types_t>
  void copy(const std::tuple<types_t...>& values, const RdKafka::Conf& from, RdKafka::Conf& to,
      const nasdaq::error_t& error) {
    (copy(std::get<types_t>(values), from, to, error), ...);
  }

  RdKafka::Conf::ConfType get_rdkafka_config_type(const nasdaq::acc::config_t::type_t& type) {
    return type == nasdaq::acc::config_t::e_global ? RdKafka::Conf::CONF_GLOBAL : RdKafka::Conf::CONF_TOPIC;
  }

} /* namespace */

namespace nasdaq {

  namespace acc {

    const config_t::strings_t config_t::param = config_t::available_parameters();

    config_t::config_t(const config_t::type_t& type)
        : m_type(type)
        , m_config(RdKafka::Conf::create(get_rdkafka_config_type(m_type))) {
    }

    config_t::config_t(const get_property_t& get_property, const error_t& error,
          const config_t::type_t& type)
        : config_t(type) {
      read_config(get_property, error);
    }

    config_t config_t::clone(const error_t& error) const {
      config_t res(m_type);
      for(const std::string& it : param) {
        std::string err;
        std::string value;
        if(RdKafka::Conf::CONF_OK == m_config->get(it, value))
          res.m_config->set(it, value, err);
        else if(std::string::npos == it.find("_cb"))
          error.error("parameter: [" + it + "] value: [" + value + "] error: [" + err + "] " + __FILE_STR__);
      }
      copy(calbacks, *m_config, *res.m_config, error);
      return res;
    }

    void config_t::read_config(const get_property_t& get_property, const error_t& error) {
      const auto& p = param;
      std::string err;
      for(const auto& it : p/*aram*/)
        if(const auto& tmp = get_property(it))
          if(RdKafka::Conf::CONF_OK != m_config->set(it, *tmp, err))
            error.error(err);
    }

    void config_t::set(RdKafka::DeliveryReportCb* value, const error_t& error) {
      std::string err;
      if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err))
        error.error(err);
    }

    void config_t::set(RdKafka::OAuthBearerTokenRefreshCb* value, const error_t& error) {
      std::string err;
      const auto& f = get_name(value);
      if(RdKafka::Conf::CONF_OK != m_config->set(f, value, err))
        error.error(err);
    }

    void config_t::set(RdKafka::EventCb* value, const error_t& error) {
      std::string err;
      if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err))
        error.error(err);
    }

    void config_t::set(const std::string& name, RdKafka::Conf* value, const error_t& error) {
      std::string err;
      if(RdKafka::Conf::CONF_OK != m_config->set(name, value, err))
        error.error(err);
    }

    void config_t::set(RdKafka::PartitionerCb* value, const error_t& error) {
      std::string err;
      if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err))
        error.error(err);
    }

    void config_t::set(RdKafka::PartitionerKeyPointerCb* value, const error_t& error) {
      std::string err;
      if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err))
        error.error(err);
    }

    void config_t::set(RdKafka::SocketCb* value, const error_t& error) {
      std::string err;
      if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err))
        error.error(err);
    }

    void config_t::set(RdKafka::OpenCb* value, const error_t& error) {
      std::string err;
      if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err))
        error.error(err);
    }

    void config_t::set(RdKafka::RebalanceCb* value, const error_t& error) {
      std::string err;
      if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err))
        error.error(err);
    }

    void config_t::set(RdKafka::OffsetCommitCb* value, const error_t& error) {
      std::string err;
      if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err))
        error.error(err);
    }

    void config_t::set(RdKafka::SslCertificateVerifyCb* value, const error_t& error) {
      std::string err;
      if(RdKafka::Conf::CONF_OK != m_config->set(get_name(value), value, err))
        error.error(err);
    }

    void config_t::set(RdKafka::ConsumeCb* value, const error_t& error) {
      std::string err;
      if(RdKafka::Conf::CONF_OK != m_config->set("consume_cb", value, err))
        error.error(err);
    }

    RdKafka::DeliveryReportCb* config_t::get(RdKafka::DeliveryReportCb* value, const error_t& error) {
      RdKafka::DeliveryReportCb* tmp;
      if(RdKafka::Conf::CONF_OK != m_config->get(tmp))
        error.info("prarameter: " + get_name(value) + ", is not set." + __FILE_STR__);
      return tmp;
    }
    RdKafka::OAuthBearerTokenRefreshCb* config_t::get(RdKafka::OAuthBearerTokenRefreshCb* value, const error_t& error) {
      RdKafka::OAuthBearerTokenRefreshCb* tmp;
      if(RdKafka::Conf::CONF_OK != m_config->get(tmp))
        error.info("prarameter: " + get_name(value) + ", is not set." + __FILE_STR__);
      return tmp;
    }
    RdKafka::EventCb* config_t::get(RdKafka::EventCb* value, const error_t& error) {
      RdKafka::EventCb* tmp;
      if(RdKafka::Conf::CONF_OK != m_config->get(tmp))
        error.info("prarameter: " + get_name(value) + ", is not set." + __FILE_STR__);
      return tmp;
    }
    RdKafka::PartitionerCb* config_t::get(RdKafka::PartitionerCb* value, const error_t& error) {
      RdKafka::PartitionerCb* tmp;
      if(RdKafka::Conf::CONF_OK != m_config->get(tmp))
        error.info("prarameter: " + get_name(value) + ", is not set." + __FILE_STR__);
      return tmp;
    }
    RdKafka::PartitionerKeyPointerCb* config_t::get(RdKafka::PartitionerKeyPointerCb* value, const error_t& error) {
      RdKafka::PartitionerKeyPointerCb* tmp;
      if(RdKafka::Conf::CONF_OK != m_config->get(tmp))
        error.info("prarameter: " + get_name(value) + ", is not set." + __FILE_STR__);
      return tmp;
    }
    RdKafka::SocketCb* config_t::get(RdKafka::SocketCb* value, const error_t& error) {
      RdKafka::SocketCb* tmp;
      if(RdKafka::Conf::CONF_OK != m_config->get(tmp))
        error.info("prarameter: " + get_name(value) + ", is not set." + __FILE_STR__);
      return tmp;
    }
    RdKafka::OpenCb* config_t::get(RdKafka::OpenCb* value, const error_t& error) {
      RdKafka::OpenCb* tmp;
      if(RdKafka::Conf::CONF_OK != m_config->get(tmp))
        error.info("prarameter: " + get_name(value) + ", is not set." + __FILE_STR__);
      return tmp;
    }
    RdKafka::RebalanceCb* config_t::get(RdKafka::RebalanceCb* value, const error_t& error) {
      RdKafka::RebalanceCb* tmp;
      if(RdKafka::Conf::CONF_OK != m_config->get(tmp))
        error.info("prarameter: " + get_name(value) + ", is not set." + __FILE_STR__);
      return tmp;
    }
    RdKafka::OffsetCommitCb* config_t::get(RdKafka::OffsetCommitCb* value, const error_t& error) {
      RdKafka::OffsetCommitCb* tmp;
      if(RdKafka::Conf::CONF_OK != m_config->get(tmp))
        error.info("prarameter: " + get_name(value) + ", is not set." + __FILE_STR__);
      return tmp;
    }
    RdKafka::SslCertificateVerifyCb* config_t::get(RdKafka::SslCertificateVerifyCb* value, const error_t& error) {
      RdKafka::SslCertificateVerifyCb* tmp;
      if(RdKafka::Conf::CONF_OK != m_config->get(tmp))
        error.info("prarameter: " + get_name(value) + ", is not set." + __FILE_STR__);
      return tmp;
    }

    void config_t::set(const std::string& name, const std::string& value, const error_t& error) {
      std::string err;
      if(RdKafka::Conf::CONF_OK != m_config->set(name, value, err))
        error.error(err + __FILE_STR__);
    }

    void config_t::get(const std::string& name, std::string& value, const error_t& error) {
      if(RdKafka::Conf::CONF_OK != m_config->get(name, value))
        error.error("prarameter: " + name + ", is not set." + __FILE_STR__);
    }

    RdKafka::Conf* config_t::get_config() const {
      return m_config.get();
    }

    const config_t::type_t& config_t::get_type() const {
      return m_type;
    }

    void config_t::print() const {
      int idx = 0;
      for(const auto& it : *m_config->dump())
        std::cout << it << (idx++ % 2 == 0 ?  '=' : '\n');
    }

    config_t::strings_t config_t::available_parameters() {
      config_t::strings_t res;
      char* buf;
      size_t len;
      if(auto stream = open_memstream(&buf, &len)) {
        rd_kafka_conf_properties_show(stream);
        fflush (stream);
        char* tmp = 0;
        while(0 < getline(&tmp, &len, stream))
          if(0 != std::islower(*tmp))
            res.push_back(std::string(tmp, std::strchr(tmp, ' ')));
        fclose(stream);
        free(buf);
      }
      return res;
    }

  } /* namespace acc */

} /* namespace nasdaq */
