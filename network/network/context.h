#pragma once

#include "nettypes.h"

namespace net {

  class context_t {
  public:
    virtual ~context_t() = default;
    virtual void run() = 0;
    virtual std::size_t run_one(error_code_t& err) = 0;
    virtual void stop() = 0;
    virtual const error_handle_t& get_error_handle() = 0;
  public:
    static context_ptr create(const error_handle_t& handelr);
  };

} /* namespace net */
