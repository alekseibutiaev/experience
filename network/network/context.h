#pragma once

#include "nettypes.h"

namespace net {

  class context_t {
  public:
    virtual ~context_t() = default;
    virtual void run() = 0;
    virtual void stop() = 0;
  public:
    static context_ptr create();
  };

} /* namespace net */
