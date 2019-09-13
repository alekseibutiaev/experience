#include <iterator>

#include <boost/lexical_cast.hpp>

#include "socket_details.h"
#include "session.h"

namespace {

  void keep_session(const net::session_ptr) {
  }

  const auto defalloc = [](const net::buffer_t::value_type* data, std::size_t size) {
      return net::buffer_ptr(new net::buffer_t(data, data + size)); };

} /* namespace */

namespace net {

  session_t::session_t(details::socket_ptr&& socket)
    : m_is_open(true)
    , m_socket(std::move(socket))
    , m_buffer_allocator(defalloc)
    , m_recv_buf(new recv_buf_t::element_type[max_buffer]) {
  }

  session_t::~session_t() {
    close();
  }

  void session_t::read() {
    if(m_is_open.load())
      m_socket->async_read_some(boost::asio::buffer(m_recv_buf.get(), max_buffer),
        std::bind(&session_t::read_handler, this, std::placeholders::_1, std::placeholders::_2 ));
  }

  void session_t::send(const buffer_ptr& value) {
    if(m_is_open.load())
      m_socket->async_write_some(boost::asio::buffer(value->data(), value->size()),
        std::bind(&session_t::write_handler, this, value, std::placeholders::_1, std::placeholders::_2));
  }

  void session_t::close() {
    close(boost::system::errc::make_error_code(boost::system::errc::success));
  }

  const std::string& session_t::address() const {
    if(m_addres.empty())
      m_addres = boost::lexical_cast<std::string>(m_socket->remote_endpoint());
    return m_addres;
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
    if(m_is_open.exchange(false)) {
#if 0
      if(!m_socket->get_io_service().stopped())
        m_socket->get_io_service().post(std::bind(&keep_session, shared_from_this()));
#else
      m_socket->get_io_service().post(std::bind(&keep_session, shared_from_this()));
#endif
      m_socket->close();
      if(m_disconnect)
        m_disconnect(shared_from_this(), value);
    }
  }

  void session_t::write_handler(const buffer_ptr buf, const error_code_t& err, std::size_t transferred){
    if(err)
      close(err);
  }

  void session_t::read_handler(const error_code_t& err, std::size_t transferred) {
    if(err) 
      close(err);
    else if(m_receive) {
      m_receive(m_buffer_allocator(m_recv_buf.get(), transferred));
      read();
    }
  }

} /* namespace net */
