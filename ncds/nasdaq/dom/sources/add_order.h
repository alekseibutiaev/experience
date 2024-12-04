#pragma once

#include "../../message.h"
#include "../dom_types.h"

namespace nasdaq {

  namespace dom {

    class add_order_t : public message_t {
    public:
      add_order_t(const message_t& value);
    };

  } /* namespace dom */

} /* namespace nasdaq */
