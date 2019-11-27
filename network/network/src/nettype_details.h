#pragma once

#include <boost/version.hpp>
#include <boost/asio.hpp>

namespace net {

  namespace details {

#if BOOST_VERSION <= 106501
      using io_context_t = boost::asio::io_service;
#else
      using io_context_t = boost::asio::io_context;
#endif

  } /* namespace details */

} /* namespace net */
