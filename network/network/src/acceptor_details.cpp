
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

    void acceptor_t::start() {
      m_socket.reset(new details::socket_t(static_cast<details::context_t&>(*m_context).get_io_context()));
      m_acceptor.async_accept(*m_socket, std::bind(&acceptor_t::accepted_handler, this, std::ref(m_socket),
          std::placeholders::_1));
    }

    void acceptor_t::accepted_callback(const accepted_func_t& value) {
      m_accepted = value;
    }

    void acceptor_t::accepted_handler(details::socket_ptr& socket, const error_code_t& err) {
      if(!err) {
        if(m_accepted)
          m_accepted(net::session_t::create(std::move(socket)));
        start();
      }
    }

  } /* namespace details */

} /* namespace net */
