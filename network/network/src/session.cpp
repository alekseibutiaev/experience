#include <iterator>
#include <functional>

#include <boost/lexical_cast.hpp>

#include "nettype_details.h"
#include "socket_details.h"
#include "session.h"

namespace {

  void keep_session(const net::session_ptr) {
  }

  const auto defalloc = [](const net::buffer_t::value_type* data, std::size_t size) {
    return net::buffer_ptr(new net::buffer_t(data, data + size));
  };

  net::details::io_context_t& get_context(net::details::socket_ptr& socket) {
#if BOOST_VERSION <= 106501
    return socket->get_io_service();
#else
    return socket->get_executor().context();
#endif
  }

  void local_post(net::details::io_context_t& ctx, std::function<void()> func) {
#if BOOST_VERSION <= 106501
    ctx.post(func);
#else
    boost::asio::post(ctx, func);
#endif
  }

} /* namespace */

namespace net {

  session_t::session_t(details::socket_ptr&& socket)
    : m_is_open(true)
    , m_socket(std::move(socket))
    , m_buffer_allocator(defalloc)
    , m_recv_buf(new recv_buf_t::element_type[max_buffer]) {
  }

  session_t::~session_t() {
  }

  void session_t::read() {
    if(m_is_open.load())
      m_socket->async_read_some(boost::asio::buffer(m_recv_buf.get(), max_buffer),
        std::bind(&session_t::read_handler, this, std::placeholders::_1, std::placeholders::_2));
  }

  void session_t::send(const buffer_ptr& value, const std::size_t offset) {
    if(m_is_open.load())
      m_socket->async_write_some(boost::asio::buffer(value->data() + offset, value->size() - offset),
        std::bind(&session_t::write_handler, this, write_buf_t(value, offset), std::placeholders::_1,
          std::placeholders::_2));
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

  void session_t::receive_callback(const receive_data_t& value) {
    m_receive = value;
  }

  void session_t::disconnect_callback(const socket_events_t& value) {
    m_disconnect = value;
  }

  session_ptr session_t::create(details::socket_ptr&& value) {
    return session_ptr(new session_t(std::move(value)));
  }

#if defined(DEBUG)
  unsigned long long session_t::sockets() {
    return details::socket_ptr::element_type::m_counrer;
  }
#endif

  void session_t::close(const error_code_t& value) {
    if(m_is_open.exchange(false)) {
      local_post(get_context(m_socket), std::bind(&keep_session, shared_from_this()));
      m_socket->close();
      if(m_disconnect)
        m_disconnect(shared_from_this(), value);
    }
  }

  void session_t::write_handler(const write_buf_t buf, const error_code_t& err, std::size_t transferred){
    if(err)
      close(err);
    else if(buf.first->size() - buf.second > transferred)
      send(buf.first, buf.second + transferred);
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
