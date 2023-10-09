#include <string>
#include <stdexcept>

#include "oauthbearer.h"

namespace {

  const std::string param_uri = "oauth.token.endpoint.uri";
  const std::string param_glient_id = "oauth.client.id";
  const std::string param_secret = "oauth.client.secret";

  kf::string_try_t get_param(const kf::get_property_t& get_property, const std::string& name) {
    if(const auto tmp = get_property(name))
      return tmp;
    throw(std::runtime_error("parametrs: " + name + " is not availavle"));
  }

} /* namespace */

namespace kf {

  oauthbearer_t::oauthbearer_t(const get_property_t& get_property)
    : m_uri(*get_param(get_property, param_uri))
    , m_glient_id(*get_param(get_property, param_glient_id))
    , m_secret(*get_param(get_property, param_secret))
    , m_get_property(get_property) {
  }

  void oauthbearer_t::oauthbearer_token_refresh_cb(RdKafka::Handle* handle, const std::string& oauthbearer_config) {

  }

} /* namespace kf */
