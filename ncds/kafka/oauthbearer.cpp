#include "oauthbearer.h"

namespace kf {

  oauthbearer_t::oauthbearer_t(const get_property_t& params)
    : m_params(params) {
  }

  void oauthbearer_t::oauthbearer_token_refresh_cb(RdKafka::Handle* handle, const std::string& oauthbearer_config) {

  }

} /* namespace kf */
