#pragma once

#include <atomic>
#include <string>
#include <memory>
#include <utility>

#include "nettypes.h"

namespace net {

  class session_t : public std::enable_shared_from_this<session_t> {
  public:
    virtual ~session_t() = default;
    virtual void read() = 0;
    virtual void send(const buffer_ptr& value, const std::size_t offset = 0) = 0;
    virtual const std::string& address() const = 0;
    void close();
    void buffer_allocator(const buffer_allocator_t& value);
    void receive_callback(const receive_data_t& value);
    void disconnect_callback(const socket_events_t& value);
  public:
#if defined(DEBUG)
    static unsigned long long sockets();
#endif
  protected:
    using recv_buf_t = std::unique_ptr<buffer_t::value_type[]>;
    using write_buf_t = std::pair<const buffer_ptr, std::size_t>;
  protected:
    session_t();
  protected:
    std::atomic_bool m_is_open;
    buffer_allocator_t m_buffer_allocator;
    recv_buf_t m_recv_buf;
    receive_data_t m_receive;
    socket_events_t m_disconnect;
    mutable std::string m_addres;
  protected:
    const static std::size_t max_buffer = 10240;
  private:
    virtual void write_handler(const write_buf_t buf, const error_code_t& err, std::size_t transferred) = 0;
    virtual void read_handler(const error_code_t& err, std::size_t transferred) = 0;
    virtual void close(const error_code_t& value) = 0;
  };

} /* namespace net */
