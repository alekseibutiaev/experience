
#include "session.h"
#include "context_details.h"
#include "socket_details.h"

#include "acceptor_details.h"

namespace net {

  namespace details {

    acceptor_t::acceptor_t(context_ptr& context, unsigned short port)
      : m_context(context)
      , m_acceptor(static_cast<details::context_t&>(*m_context).get_io_context(),
          boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
    }

    acceptor_t::~acceptor_t() {
      m_acceptor.close();
    }

    void acceptor_t::listen() {
      m_socket.reset(new details::socket_t(static_cast<details::context_t&>(*m_context).get_io_context()));
      m_acceptor.async_accept(*m_socket, std::bind(&acceptor_t::accepted_handler, this, std::ref(m_socket),
          std::placeholders::_1));
    }

    void acceptor_t::close() {
      m_acceptor.close();
    }

    void acceptor_t::accepted_callback(const socket_events_t& value) {
      m_accepted = value;
    }

    void acceptor_t::accepted_handler(details::socket_ptr& socket, const error_code_t& err) {
      if(m_accepted)
        m_accepted(err ? net::session_ptr() : net::session_t::create(std::move(socket)), err);
      if(m_acceptor.is_open())
        listen();
    }

  } /* namespace details */

  acceptor_ptr acceptor_t::create(context_ptr& context, unsigned short port) {
    return acceptor_ptr(new net::details::acceptor_t(context, port));
  }

} /* namespace net */
