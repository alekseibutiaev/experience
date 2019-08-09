#include <iterator>

#include "socket_details.h"
#include "session.h"

namespace {

  void keep_session(const net::session_ptr) {
  }

  net::buffer_ptr default_allocaror(const net::buffer_t::value_type* data, std::size_t size) {
    return net::buffer_ptr(new net::buffer_t(data, data + size));
  }

} /* namespace */

namespace net {

  session_t::session_t(details::socket_ptr&& socket)
    : m_socket(std::move(socket))
    , m_buffer_allocator(std::bind(&default_allocaror, std::placeholders::_1, std::placeholders::_2))
    , m_buf(max_buffer) {
  }

  session_t::~session_t() {
    close();
  }

  void session_t::read() {
    if(m_socket->is_open())
      m_socket->async_read_some(boost::asio::buffer(m_buf.data(), m_buf.size()),
        std::bind(&session_t::read_handler, this, std::ref(m_buf), m_receive, std::placeholders::_1, std::placeholders::_2 ));
  }

  void session_t::send(const buffer_ptr& value) {
    if(m_socket->is_open())
      m_socket->async_write_some(boost::asio::buffer(value->data(), value->size()),
        std::bind(&session_t::write_handler, this, value, std::placeholders::_1, std::placeholders::_2));
  }

  void session_t::close() {
    close(boost::system::errc::make_error_code(boost::system::errc::success));
  }

  void session_t::buffer_allocator(const buffer_allocator_t& value) {
    m_buffer_allocator = value;
  }

  void session_t::receive_callback(const receive_func_t& value) {
    m_receive = value;
  }

  void session_t::disconnect_callback(const disconnect_func_t& value) {
    m_disconnect = value;    
  }

  session_ptr session_t::create(details::socket_ptr&& value) {
    return session_ptr(new session_t(std::move(value)));
  }

  void session_t::close(const error_code_t& value) {
    if(m_socket->is_open()) {
      m_socket->get_io_service().post(std::bind(&keep_session, shared_from_this()));
      m_socket->close();
      if(m_disconnect)
        m_disconnect(shared_from_this(), value);
    }
  }

  void session_t::write_handler(const buffer_ptr buf, const error_code_t& err, std::size_t transferred){
    if(err)
      close(err);
  }

  void session_t::read_handler(const buffer_t& buf, const receive_func_t func,
      const error_code_t& err, std::size_t transferred) {
    if(err) 
      close(err);
    else if(func) {
      func(m_buffer_allocator(buf.data(), transferred));
      read();
    }
  }

} /* namespace net */