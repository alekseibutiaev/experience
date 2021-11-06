#pragma once

#include <string>

#include "nettypes.h"

namespace net {

  class connector_t {
  public:
    static session_ptr connect(context_ptr& context, const std::string& host, const unsigned short& port);
    static session_ptr connect(context_ptr& context, const std::string& host, const std::string& port);
    static void connect(context_ptr& context, const std::string& host, const unsigned short& port, socket_events_t func);
    static void connect(context_ptr& context, const std::string& host, const std::string& port, socket_events_t func);
  };

} /* namespace net */
