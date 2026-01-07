#include "../tw_visitor.h"
#include "system_event.h"

namespace nasdaq {

  namespace tw {

    system_event_t::system_event_t(const message_t& value) : base_t(value) {
    }

    void system_event_t::visitor(message_visitor_t& visitor) const {
      try {
        dynamic_cast<tw_visitor_t&>(visitor).visit(*this);
      }
      catch(const std::bad_cast& e) {
      }
    }

    const int& system_event_t::symbol_locale() const {
      return std::get<int>(m_values[e_symbol_locale]);
    }

    const time_point_t& system_event_t::time_stamp() const {
      return std::get<time_point_t>(m_values[e_time_stamp]);
    }

    const std::string& system_event_t::event() const {
      return std::get<std::string>(m_values[e_event]);
    }

  } /* namespace tw */

} /* namespace nasdaq */
