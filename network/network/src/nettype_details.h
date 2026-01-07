#pragma once

#include <boost/version.hpp>
#include <boost/asio.hpp>

namespace net {

  namespace details {

#if BOOST_VERSION < 106600
      using io_context_t = boost::asio::io_service;
#else
      using io_context_t = boost::asio::io_context;
#endif

    using tcp_ip_protocol_t = boost::asio::ip::tcp;
    using local_stream_protocol_t = boost::asio::local::stream_protocol;

  } /* namespace details */

} /* namespace net */
