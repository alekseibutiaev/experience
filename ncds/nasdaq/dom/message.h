#pragma once

#include "dom_types.h"

namespace nasdaq {

  namespace dom {

    class message_t {
    public:
      virtual ~message_t() = default;
      virtual value_t& operator[](const std::size_t idx) = 0;
      virtual const value_t& operator[](const std::size_t idx) const = 0;
      virtual std::size_t size() const = 0;
    };

  } /* namespace dom */

} /* namespace nasdaq */

