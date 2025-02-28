#include <iostream>
#include <chrono>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include "http_request.h"
#include "oauthbearer.h"

namespace {

  const std::string param_uri = "oauth.token.endpoint.uri";
  const std::string param_glient_id = "oauth.client.id";
  const std::string param_secret = "oauth.client.secret";

  nasdaq::string_try_t get_param(const nasdaq::get_property_t& get_property, const std::string& name) {
    if(const auto tmp = get_property(name))
      return tmp;
    throw(std::runtime_error("parametrs: " + name + " is not availavle"));
  }

} /* namespace */

namespace nasdaq {

  namespace acc {

    oauthbearer_t::oauthbearer_t(const get_property_t& get_property)
      : m_uri(*get_param(get_property, param_uri))
      , m_glient_id(*get_param(get_property, param_glient_id))
      , m_secret(*get_param(get_property, param_secret))
      , m_get_property(get_property) {
    }

    void oauthbearer_t::oauthbearer_token_refresh_cb(RdKafka::Handle* handle, const std::string& /*oauthbearer_config*/) {
      try {
        const std::string data = "grant_type=client_credentials&client_id=" + m_glient_id + "&client_secret=" + m_secret + "&getAccounts=1";
        http_request_t http(m_uri);
        http.set_headers("Content-Type: application/x-www-form-urlencoded", "charsets: utf-8", "Accept: application/json");
        http.ssl_verify_peer(0);
        http.ssl_verify_host(0);
        const auto& res = http.post(data.c_str());
        nlohmann::json j = nlohmann::json::parse(res.second);
        std::chrono::milliseconds expires_in(j["expires_in"].template get<long>() * 1000);
        std::string token = j["access_token"];
        auto ts = std::chrono::time_point_cast<std::chrono::milliseconds>(
          std::chrono::system_clock::now()) + expires_in;
        std::string err;
        if(RdKafka::ErrorCode::ERR_NO_ERROR != handle->oauthbearer_set_token(token,
            ts.time_since_epoch().count(), "infrontasa-annika-norberg", {}, err )) {
          /*RdKafka::ErrorCode tok_failure_err = */handle->oauthbearer_set_token_failure(err);
        }
      }
      catch(const std::exception& e) {
      }
    }

  } /* namespace acc */

} /* namespace nasdaq */
