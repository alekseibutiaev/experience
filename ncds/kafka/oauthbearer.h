#pragma once

#include <librdkafka/rdkafkacpp.h>

#include <types.h>

namespace kf {

  class oauthbearer_t : public RdKafka::OAuthBearerTokenRefreshCb {
  public:
    oauthbearer_t(const get_property_t& params);
  private:
    void oauthbearer_token_refresh_cb(RdKafka::Handle* handle, const std::string& oauthbearer_config) override;
  private:
    const get_property_t& m_params;
  };
  
} /* namespace kf */