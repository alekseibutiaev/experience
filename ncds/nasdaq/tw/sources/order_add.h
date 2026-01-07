#pragma once

#include "../tw_types.h"
#include "base.h"

namespace nasdaq {

  namespace tw {

    class order_add_t : public base_t {
    public:
      enum { e_symbol_locale = 3, e_time_stamp, e_id, e_side, e_quantity, e_symbol, e_price };
    public:
      order_add_t(const message_t& value);
      void visitor(message_visitor_t& visitor) const override;
      const int& symbol_locale() const;
      const time_point_t& time_stamp() const;
      const long& id() const;
      const std::string& side() const;
      const int& quantity() const;
      const std::string& symbol() const;
      const int& price() const;
    };

  } /* namespace tw */

} /* namespace nasdaq */
