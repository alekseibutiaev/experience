#include "add_order.h"

namespace nasdaq {

  namespace dom {

//       enum { e_symbol_locale = 3, e_time_stamp, e_id, e_side, e_quantity, e_symbol, e_price };


    add_order_t::add_order_t(const message_t& value) : message_t(value) {

    }

    const int& add_order_t::symbol_locale() const {
      return std::get<int>(m_values[e_symbol_locale]);
    }

    const time_point_t& add_order_t::time_stamp() const {
      return std::get<time_point_t>(m_values[e_time_stamp]);

    }
    const long& add_order_t::id() const {
      return std::get<long>(m_values[e_id]);
    }

    const std::string& add_order_t::side() const {
      return std::get<std::string>(m_values[e_side]);
    }

    const int& add_order_t::quantity() const {
      return std::get<int>(m_values[e_quantity]);
    }

    const std::string& add_order_t::symbol() const {
      return std::get<std::string>(m_values[e_symbol]);
    }

    const int& add_order_t::price() const {
      return std::get<int>(m_values[e_price]);
    }


  } /* namespace dom */

} /* namespace nasdaq */
