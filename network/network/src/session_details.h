#pragma once

#include <atomic>
#include <memory>
#include <functional>

#include <boost/asio.hpp>
//#include <boost/asio/ssl.hpp>
#include <boost/lexical_cast.hpp>

#include "nettype_details.h"
#include "session.h"

namespace {

  void keep_session(const net::session_ptr) {
  }

  template<typename socket_t>
  net::details::io_context_t& get_context(socket_t& socket) {
#if BOOST_VERSION < 106600
    return socket.get_io_service();
#elif BOOST_VERSION < 107000
    return socket.get_executor().context();
#else
    auto* tmp =  socket.get_executor().template target<net::details::io_context_t>();
    return *tmp;
#endif
  }

  void local_post(net::details::io_context_t& ctx, std::function<void()> func) {
#if BOOST_VERSION < 106600
    ctx.post(func);
#else
    boost::asio::post(ctx, func);
#endif
  }

} /* namespace */


namespace net {

  namespace details {

    template<typename protocol_t>
    class session_t : public net::session_t {
    public:
      using protocol_type = protocol_t;
      using socket_type = typename protocol_t::socket;
    public:
      session_t(socket_type&& socket)
        : m_socket(std::move(socket)) {
      }
    private:
      void read() override {
        if(m_is_open.load())
          m_socket.async_read_some(boost::asio::buffer(m_recv_buf.get(), max_buffer),
            std::bind(&session_t::read_handler, this, std::placeholders::_1, std::placeholders::_2));
      }
      void send(const buffer_ptr& value, const std::size_t offset = 0) override {
        if(m_is_open.load())
          m_socket.async_write_some(boost::asio::buffer(value->data() + offset, value->size() - offset),
            std::bind(&session_t::write_handler, this, write_buf_t(value, offset), std::placeholders::_1,
              std::placeholders::_2));
      }
      const std::string& address() const override {
        if(m_addres.empty())
          m_addres = boost::lexical_cast<std::string>(m_socket.remote_endpoint());
        return m_addres;
      }
      void close(const error_code_t& value) override {
        if(m_is_open.exchange(false)) {
          local_post(get_context(m_socket), std::bind(&keep_session, shared_from_this()));
          m_socket.close();
          if(m_disconnect)
            m_disconnect(shared_from_this(), value);
        }
      }
      void write_handler(const write_buf_t buf, const error_code_t& err, std::size_t transferred) override {
        if(err)
          close(err);
        else if(buf.first->size() - buf.second > transferred)
          send(buf.first, buf.second + transferred);
      }
      void read_handler(const error_code_t& err, std::size_t transferred) override {
        if(err) 
          close(err);
        else if(m_receive) {
          m_receive(m_buffer_allocator(m_recv_buf.get(), transferred));
          read();
        }
      }
    private:
      socket_type m_socket;
    };

  } /* namespace details */

} /* namespace net */
