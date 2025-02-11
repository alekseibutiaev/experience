#pragma once

#include "../../message.h"
#include "../dom_types.h"

namespace nasdaq {

  namespace dom {

    class add_order_t : public message_t {
    public:
      enum { e_symbol_locale = 3, e_time_stamp, e_id, e_side, e_quantity, e_symbol, e_price };
    public:
      add_order_t(const message_t& value);
      const int& symbol_locale() const;
      const time_point_t& time_stamp() const;
      const long& id() const;
      const std::string& side() const;
      const int& quantity() const;
      const std::string& symbol() const;
      const int& price() const;
    };

  } /* namespace dom */

} /* namespace nasdaq */
