#include "../dom_visitor.h"
#include "order_executed.h"

namespace nasdaq {

  namespace dom {

    order_executed_t::order_executed_t(const message_t& value) : base_t(value) {
    }

    void order_executed_t::visitor(message_visitor_t& visitor) const {
      try {
        dynamic_cast<dom::dom_visitor_t&>(visitor).visit(*this);
      }
      catch(const std::bad_cast& e) {
      }
    }

    const int& order_executed_t::symbol_locale() const {
      return std::get<int>(m_values[e_symbol_locale]);
    }

    const time_point_t& order_executed_t::time_stamp() const {
      return std::get<time_point_t>(m_values[e_time_stamp]);
    }

    const long& order_executed_t::id() const {
      return std::get<long>(m_values[e_id]);
    }

    const int& order_executed_t::quantity() const {
      return std::get<int>(m_values[e_quantity]);
    }

    const long& order_executed_t::matchid() const {
      return std::get<long>(m_values[e_matchid]);
    }

  } /* namespace dom */

} /* namespace nasdaq */
