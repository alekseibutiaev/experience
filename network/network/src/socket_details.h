#pragma once

#include <boost/asio.hpp>

namespace net {

  namespace details {

    class socket_t : public boost::asio::ip::tcp::socket {
    private:
      using patent_t = boost::asio::ip::tcp::socket;
    public:
      using patent_t::patent_t;
/*
      using patent_t::close;
      using patent_t::is_open;
      using patent_t::async_read_some;
      using patent_t::async_write_some;
      using patent_t::get_io_service;
*/
    };

  } /* namespace details */

} /* namespace net */