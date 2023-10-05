#pragma once

#include <memory>

#include <types.h>


namespace kf {

  class config_t;

  class consumer_t {
  public:
    consumer_t(const config_t& config, const get_property_t& get_property, const error_t& notify);
  private:
    using auth_ptr = std::shared_ptr<RdKafka::OAuthBearerTokenRefreshCb>;
  private:
    config_t m_config;
    const get_property_t& m_get_property;
    auth_ptr m_auth;
  };

} /* namespace kf */
