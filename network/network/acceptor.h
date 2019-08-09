#pragma once

#include "nettypes.h"

namespace net {

  class acceptor_t {
  public:
    virtual ~acceptor_t() = default;
    virtual void start() = 0;
    virtual void accepted_callback(const accepted_func_t& value) = 0;
  public:
    static acceptor_ptr create(context_ptr& context, unsigned short port);
  };

} /* namespace net */
