#include "../dom_visitor.h"
#include "order_executed_with_price.h"

namespace nasdaq {

  namespace dom {

    order_executed_with_price_t::order_executed_with_price_t(const message_t& value) : base_t(value) {
    }

    void order_executed_with_price_t::visitor(message_visitor_t& visitor) const {
      try {
        dynamic_cast<dom::dom_visitor_t&>(visitor).visit(*this);
      }
      catch(const std::bad_cast& e) {
      }
    }

    const int& order_executed_with_price_t::symbol_locale() const {
      return std::get<int>(m_values[e_symbol_locale]);
    }

    const time_point_t& order_executed_with_price_t::time_stamp() const {
      return std::get<time_point_t>(m_values[e_time_stamp]);
    }

    const long& order_executed_with_price_t::id() const {
      return std::get<long>(m_values[e_id]);
    }

    const int& order_executed_with_price_t::quantity() const {
      return std::get<int>(m_values[e_quantity]);
    }

    const long& order_executed_with_price_t::matchid() const {
      return std::get<long>(m_values[e_matchid]);
    }

    const std::string& order_executed_with_price_t::printable() const {
      return std::get<std::string>(m_values[e_printable]);
    }

    const int& order_executed_with_price_t::price() const {
      return std::get<int>(m_values[e_price]);
    }

  } /* namespace dom */

} /* namespace nasdaq */
