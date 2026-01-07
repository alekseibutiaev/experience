#pragma once

#include <string>

#include "nettypes.h"

namespace net {

  class connector_t {
  public:
    static session_ptr tcp_ip_v4(context_ptr& context, const std::string& host,
      const unsigned short& port, error_code_t& err);
    static session_ptr tcp_ip_v4(context_ptr& context, const std::string& host,
      const std::string& port, error_code_t& err);
    static void tcp_ip_v4(context_ptr& context, const std::string& host, const unsigned short& port, socket_events_t func);
    static void tcp_ip_v4(context_ptr& context, const std::string& host, const std::string& port, socket_events_t func);
  };

} /* namespace net */
