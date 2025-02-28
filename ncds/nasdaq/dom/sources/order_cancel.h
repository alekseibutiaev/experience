#pragma once

#include "../../message.h"
#include "../dom_types.h"

namespace nasdaq {

  namespace dom {

    class order_cancel_t : public message_t {
    public:
      enum { e_symbol_locale = 3, e_time_stamp, e_id, e_quantity };
    public:
      order_cancel_t(const message_t& value);
      void visitor(message_visitor_t& visitor) const override;
      const int& symbol_locale() const;
      const time_point_t& time_stamp() const;
      const long& id() const;
      const int& quantity() const;
    };

  } /* namespace dom */

} /* namespace nasdaq */
