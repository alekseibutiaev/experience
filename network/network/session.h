#pragma once

#include <atomic>
#include <string>
#include <memory>
#include <utility>

#include "nettypes.h"

namespace net {

  class session_t : public std::enable_shared_from_this<session_t> {
  public:
    ~session_t();
    void read();
    void send(const buffer_ptr& value, const std::size_t offset = 0);
    void close();
    const std::string& address() const;
    void buffer_allocator(const buffer_allocator_t& value);
    void receive_callback(const receive_data_t& value);
    void disconnect_callback(const socket_events_t& value);
  public:
    static session_ptr create(details::socket_ptr&& value);
#if defined(DEBUG)
    static unsigned long long sockets();
#endif
  private:
    using recv_buf_t = std::unique_ptr<buffer_t::value_type[]>;
    using write_buf_t = std::pair<const buffer_ptr, std::size_t>;
  private:
    session_t(details::socket_ptr&& value);
    session_t(const session_t&) = delete;
    session_t& operator=(const session_t&) = delete;
    void close(const error_code_t& value);
    void write_handler(const write_buf_t buf, const error_code_t& err, std::size_t transferred);
    void read_handler(const error_code_t& err, std::size_t transferred);
  private:
    std::atomic_bool m_is_open;
    details::socket_ptr m_socket;
    buffer_allocator_t m_buffer_allocator;
    recv_buf_t m_recv_buf;
    receive_data_t m_receive;
    socket_events_t m_disconnect;
    mutable std::string m_addres;
  private:
    const static std::size_t max_buffer = 10240;
  };

} /* namespace net */
