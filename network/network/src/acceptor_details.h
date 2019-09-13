#pragma once

#include "boost/asio.hpp"

#include "nettypes.h"
#include "socket_details.h"

#include "acceptor.h"

namespace net {

  namespace details {

    class acceptor_t : public net::acceptor_t {
    public:
      acceptor_t(context_ptr& context, unsigned short port);
      ~acceptor_t();
      void listen() override;
      void close() override;
      void accepted_callback(const accepted_func_t& value) override;
    private:
      void accepted_handler(details::socket_ptr& socket, const error_code_t& value);
    private:
      context_ptr& m_context;
      boost::asio::ip::tcp::acceptor m_acceptor;
      details::socket_ptr m_socket;
      accepted_func_t m_accepted;
    };

  } /* namespace details */

} /* namespace net */
