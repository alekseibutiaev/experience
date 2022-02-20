#include "session_details.h"

namespace net {

  session_t::session_t()
    : m_is_open(true) {
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
