#include <functional>

#include "session_details.h"

namespace {

  const auto defalloc = [](const net::buffer_t::value_type* data, std::size_t size) {
    return net::buffer_ptr(new net::buffer_t(data, data + size));
  };

} /* namespace */

namespace net {

  session_t::session_t()
    : m_is_open(true)
    , m_buffer_allocator(defalloc)
    , m_recv_buf(new recv_buf_t::element_type[max_buffer]) {
  }

  void session_t::close() {
    close(boost::system::errc::make_error_code(boost::system::errc::success));
  }

  void session_t::buffer_allocator(const buffer_allocator_t& value) {
    m_buffer_allocator = value;
  }

  void session_t::receive_callback(const receive_data_t& value) {
    m_receive = value;
  }

  void session_t::disconnect_callback(const socket_events_t& value) {
    m_disconnect = value;
  }

} /* namespace net */
