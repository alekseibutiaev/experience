#pragma once

#include <boost/asio.hpp>

#include "context.h"

namespace net {

  namespace details {

    class context_t : public net::context_t {
    public:
      using io_context_t = boost::asio::io_service;
    public:
      void run() override;
      void stop() override;
      io_context_t& get_io_context();
    private:
      io_context_t m_io_context;
    };

  } /* namespace details */

} /* namespace net */