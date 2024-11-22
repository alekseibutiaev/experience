#pragma once

#include "dom_types.h"
#include "values.h"
#include "message.h"

namespace nasdaq {

  namespace dom {

    class addorder_t : public message_t {
    public:
      enum fields_t { e_ts, e_id, e_side, e_quantity, e_price, e_sympbol_loc, e_sympbol, e_count };
    public:
      addorder_t();
      nasdaq::time_point_t& ts();
      const nasdaq::time_point_t& ts() const;
      long& id();
      const long& id() const;
      std::string& side();
      const std::string& side() const;
      int& quantity();
      const int& quantity() const;
      int& price();
      const int& price() const;
      int& sympbol_loc();
      const int& sympbol_loc() const;
      std::string& sympbol();
      const std::string& sympbol() const;
      value_t& operator[](const std::size_t idx) override;
      const value_t& operator[](const std::size_t idx) const override;
      std::size_t size() const override;
    private:
      using values_t = dom::values_t<addorder_t::e_count>;
    private:
      values_t m_values; 
    private:
      const values_t::indexes_t m_indexes;
    };

  } /* namespace dom */

} /* namespace nasdaq */
