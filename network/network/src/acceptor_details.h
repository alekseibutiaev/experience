#pragma once

#include "boost/asio.hpp"

#include "nettypes.h"
#include "context_details.h"
#include "session_details.h"

#include "acceptor.h"

namespace {

  void empty_error(bool, const char*, const int, const net::error_code_t&) {
  }

} /* namespace */

namespace net {

  namespace details {

    template<typename socket_t>
    class acceptor_t : public net::acceptor_t {
    public:
      using protocol_acceptor_t =  typename socket_t::protocol_type::acceptor;
    public:
      acceptor_t(context_ptr& context, protocol_acceptor_t&& acceptor)
        : m_context(context)
        , m_acceptor(std::move(acceptor))
        , m_socket(static_cast<details::context_t&>(*context).get_io_context())
        , m_error(std::bind(empty_error, std::placeholders::_1, std::placeholders::_2,
            std::placeholders::_3, std::placeholders::_4)) {
      }
      ~acceptor_t() {
        close();
      }
    private:
      void listen() override {
        m_acceptor.async_accept(m_socket, std::bind(&acceptor_t::accepted_handler, this,
            std::placeholders::_1));
      }
      void close() override {
        m_acceptor.close();
      }
      void accepted_callback(const socket_events_t& value) override {
        m_accepted = value;
      }
      void error_callback(const error_handle_t& value) override {
        m_error = value;
      }
      void accepted_handler(const error_code_t& err) {
        if(!m_acceptor.is_open()) {
          m_error(true, __FUNCTION__, __LINE__,
              boost::asio::error::make_error_code(boost::asio::error::connection_aborted));
          return;
        }
        if(err)
            m_error(false, __FUNCTION__, __LINE__, err);
        else if(m_accepted)
          m_accepted(std::make_shared<details::session_t<socket_t>>(std::move(m_socket)), err);
        listen();
      }
    private:
      context_ptr& m_context;
      protocol_acceptor_t m_acceptor;
      socket_t m_socket;
      error_handle_t m_error;
      socket_events_t m_accepted;
    };


  } /* namespace details */

} /* namespace net */
