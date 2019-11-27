#pragma once

#include <boost/asio.hpp>

namespace net {

  namespace details {

#if BOOST_VERSION <= 106501
    using tcp_socket = boost::asio::ip::tcp::socket;
#else
    using tcp_socket = boost::asio::basic_stream_socket<boost::asio::ip::tcp, boost::asio::io_context::executor_type>;
#endif

    class socket_t : public tcp_socket {
    private:
      using patent_t = tcp_socket;
    public:
      using patent_t::patent_t;
    };

  } /* namespace details */

} /* namespace net */