#pragma once

#include <memory>

#include "net_common.h"

namespace net {

  class session_t : public std::enable_shared_from_this<session_t> {
  public:
    ~session_t();
    void read();
    void send(const buffer_ptr& value);
    void close();
    void receive_callback(const receive_func_t& value);
    void disconnect_callback(const disconnect_func_t& value);
  public:
    static session_ptr create(details::socket_ptr&& value);
  private:
    session_t(details::socket_ptr&& value);
    session_t(const session_t&) = delete;
    session_t& operator=(const session_t&) = delete;
    void close(const error_code_t& value);
    void write_handler(const buffer_ptr buf, const error_code_t& err, std::size_t transferred);
    void read_handler(const buffer_t& buf, const receive_func_t func, const error_code_t& err, std::size_t transferred);
  private:
    details::socket_ptr m_socket;
    buffer_t m_buf;
    receive_func_t m_receive;
    disconnect_func_t m_disconnect;
  private:
    const static std::size_t max_buffer = 10240;
  };

} /* namespace net */
