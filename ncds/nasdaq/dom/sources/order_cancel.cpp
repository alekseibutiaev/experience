#include "order_cancel.h"

namespace nasdaq {

  namespace dom {

    order_cancel_t::order_cancel_t(const message_t& value) : message_t(value) {
    }

    const int& order_cancel_t::symbol_locale() const {
      return std::get<int>(m_values[e_symbol_locale]);
    }

    const time_point_t& order_cancel_t::time_stamp() const {
      return std::get<time_point_t>(m_values[e_time_stamp]);
    }

    const long& order_cancel_t::id() const {
      return std::get<long>(m_values[e_id]);
    }

    const int& order_cancel_t::quantity() const {
      return std::get<int>(m_values[e_quantity]);
    }

  } /* namespace dom */

} /* namespace nasdaq */
