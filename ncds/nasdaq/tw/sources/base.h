#pragma once

#include "../../message.h"
#include "../tw_types.h"

namespace nasdaq {

  namespace tw {

    class base_t : public message_t {
    public:
      enum {e_sequence = 1 };
    public:
      base_t(const message_t& value);
      const long& sequence() const;
    };

  } /* namespace tw */

} /* namespace nasdaq */