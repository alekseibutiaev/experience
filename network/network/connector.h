#pragma once

#include <string>

#include "nettypes.h"

namespace net {

  class connector_t {
  public:
    static session_ptr connector(const std::string& host, const unsigned short& port);
  };

} /* namespace net */
