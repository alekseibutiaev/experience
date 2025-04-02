#include "../tw_visitor.h"
#include "order_add.h"

namespace nasdaq {

  namespace tw {

//       enum { e_symbol_locale = 3, e_time_stamp, e_id, e_side, e_quantity, e_symbol, e_price };


    order_add_t::order_add_t(const message_t& value) : base_t(value) {
    }

    void order_add_t::visitor(message_visitor_t& visitor) const {
      try {
        dynamic_cast<tw_visitor_t&>(visitor).visit(*this);
      }
      catch(const std::bad_cast& e) {
      }
    }

    const int& order_add_t::symbol_locale() const {
      return std::get<int>(m_values[e_symbol_locale]);
    }

    const time_point_t& order_add_t::time_stamp() const {
      return std::get<time_point_t>(m_values[e_time_stamp]);

    }
    const long& order_add_t::id() const {
      return std::get<long>(m_values[e_id]);
    }

    const std::string& order_add_t::side() const {
      return std::get<std::string>(m_values[e_side]);
    }

    const int& order_add_t::quantity() const {
      return std::get<int>(m_values[e_quantity]);
    }

    const std::string& order_add_t::symbol() const {
      return std::get<std::string>(m_values[e_symbol]);
    }

    const int& order_add_t::price() const {
      return std::get<int>(m_values[e_price]);
    }


  } /* namespace tw */

} /* namespace nasdaq */
