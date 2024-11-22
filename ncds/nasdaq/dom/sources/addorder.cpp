#include "addorder.h"


namespace nasdaq {

  namespace dom {

    addorder_t::addorder_t() {

    }

    nasdaq::time_point_t& addorder_t::ts() {
      return std::get<nasdaq::time_point_t>(m_values[addorder_t::e_ts]);
    }

    const nasdaq::time_point_t& addorder_t::ts() const {
      return std::get<nasdaq::time_point_t>(m_values[addorder_t::e_ts]);
    }

    long& addorder_t::id() {
      return std::get<long>(m_values[addorder_t::e_id]);
    }

    const long& addorder_t::id() const {
      return std::get<long>(m_values[addorder_t::e_id]);
    }

    std::string& addorder_t::side() {
      return std::get<std::string>(m_values[addorder_t::e_side]);
    }

    const std::string& addorder_t::side() const {
      return std::get<std::string>(m_values[addorder_t::e_side]);
    }

    int& addorder_t::quantity() {
      return std::get<int>(m_values[addorder_t::e_quantity]);
    }

    const int& addorder_t::quantity() const {
      return std::get<int>(m_values[addorder_t::e_quantity]);
    }

    int& addorder_t::price() {
      return std::get<int>(m_values[addorder_t::e_quantity]);
    }

    const int& addorder_t::price() const {
      return std::get<int>(m_values[addorder_t::e_quantity]);
    }

    int& addorder_t::sympbol_loc() {
      return std::get<int>(m_values[addorder_t::e_sympbol_loc]);
    }

    const int& addorder_t::sympbol_loc() const {
      return std::get<int>(m_values[addorder_t::e_sympbol_loc]);
    }

    std::string& addorder_t::sympbol() {
      return std::get<std::string>(m_values[addorder_t::e_sympbol]);
    }

    const std::string& addorder_t::sympbol() const {
      return std::get<std::string>(m_values[addorder_t::e_sympbol]);
    }

  } /* namespace dom */

} /* namespace nasdaq */
