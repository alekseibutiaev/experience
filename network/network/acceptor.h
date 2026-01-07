#pragma once

#include <string>

#include "nettypes.h"

namespace net {

  class acceptor_t {
  public:
    virtual ~acceptor_t() = default;
    virtual void listen() = 0;
    virtual void close() = 0;
    virtual void accepted_callback(const socket_events_t& value) = 0;
    virtual void error_callback(const error_handle_t& value) = 0;
  public:
    static acceptor_ptr tcp_ip_v4(context_ptr& context, const unsigned short& port);
    static acceptor_ptr local_stream_protocol(context_ptr& context, const std::string& file);
  };

} /* namespace net */
