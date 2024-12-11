#include "system_event.h"

namespace nasdaq {

  namespace dom {

    system_event_t::system_event_t(const message_t& value) : message_t(value) {
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

  } /* namespace dom */

} /* namespace nasdaq */
