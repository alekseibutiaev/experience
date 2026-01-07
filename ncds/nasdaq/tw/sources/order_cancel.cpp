#include "../tw_visitor.h"
#include "order_cancel.h"

namespace nasdaq {

  namespace tw {

    order_cancel_t::order_cancel_t(const message_t& value) : base_t(value) {
    }

    void order_cancel_t::visitor(message_visitor_t& visitor) const {
      try {
        dynamic_cast<tw_visitor_t&>(visitor).visit(*this);
      }
      catch(const std::bad_cast& e) {
      }
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

  } /* namespace tw */

} /* namespace nasdaq */
