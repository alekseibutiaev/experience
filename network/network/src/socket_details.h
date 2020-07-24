#pragma once
#include <atomic>
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
#if defined(DEBUG)
      template<typename... args_t>
      socket_t(args_t&&... args)
          : tcp_socket(std::forward<args_t>(args)...){
        ++m_counrer;
      }
      ~socket_t();
    public:
      static std::atomic_ullong m_counrer;
#else
      using patent_t::patent_t;
#endif
    };

  } /* namespace details */

} /* namespace net */