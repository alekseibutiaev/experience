#pragma once

#include "../message_visitor.h"

namespace nasdaq {

  namespace tw {

    class order_add_t;
    class order_cancel_t;
    class order_delete_t;
    class order_executed_t;
    class order_executed_with_price_t;
    class system_event_t;

    class tw_visitor_t : public message_visitor_t {
    public:
      virtual ~tw_visitor_t() = default;
      virtual void visit(const order_add_t& value) = 0;
      virtual void visit(const order_cancel_t& value) = 0;
      virtual void visit(const order_delete_t& value) = 0;
      virtual void visit(const order_executed_t& value) = 0;
      virtual void visit(const order_executed_with_price_t& value) = 0;
      virtual void visit(const system_event_t& value) = 0;
    };

  } /* namespace nasdaq */

} /* namespace tw */


