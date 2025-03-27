#pragma once

#include "../../message.h"
#include "../dom_types.h"

namespace nasdaq {

  namespace dom {

    class base_t : public message_t {
    public:
      enum {e_sequence = 1 };
    public:
      base_t(const message_t& value);
      const long& sequence() const;
    };

  } /* namespace dom */

} /* namespace nasdaq */