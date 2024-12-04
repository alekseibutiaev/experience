#pragma once

#include "dom_types.h"

#include "message.h"

namespace nasdaq {

  namespace dom {

    class add_order_t : public message_t {};
    class order_cancel_t : public message_t {};
    class order_delete_t : public message_t {};
    class order_executed_t : public message_t {};
    class order_executed_with_price_t : public message_t {};
    class system_event_t : public message_t {};

  } /* namespace dom */

} /* namespace nasdaq */

