#include <config.h>
#include <consumer.h>

#include "oauthbearer.h"

namespace kf {

  consumer_t::consumer_t(const config_t& config, const get_property_t& get_property, const error_t& notify)
      : m_config(config.clone(notify))
      , m_get_property(get_property)
      , m_auth(std::make_shared<oauthbearer_t>(get_property)) {
    m_config.set(m_auth.get(), notify);
  }

} /* namespace kf */
