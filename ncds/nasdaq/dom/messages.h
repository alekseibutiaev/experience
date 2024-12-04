#pragma once

#include "dom_types.h"

//#include "sources/add_order.h"

namespace nasdaq {

  namespace dom {

    class add_order_t : public message_t {
    public:
      add_order_t(const message_t& value) : message_t(value){};
    };
    class order_cancel_t : public message_t {
    public:
      order_cancel_t(const message_t& value) : message_t(value){};
    };
    class order_delete_t : public message_t {
    public:
      order_delete_t(const message_t& value) : message_t(value){};
    };
    class order_executed_t : public message_t {
    public:
      order_executed_t(const message_t& value) : message_t(value){};
    };
    class order_executed_with_price_t : public message_t {
    public:
      order_executed_with_price_t(const message_t& value) : message_t(value){};
    };
    class system_event_t : public message_t {
    public:
      system_event_t(const message_t& value) : message_t(value){};
    };

  } /* namespace dom */

} /* namespace nasdaq */

