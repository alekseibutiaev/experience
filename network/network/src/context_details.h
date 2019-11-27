#pragma once

#include <boost/version.hpp>
#include <boost/asio.hpp>

#include "nettype_details.h"

#include "context.h"

namespace net {

  namespace details {

    class context_t : public net::context_t {
    public:
      context_t();
      void run() override;
      void stop() override;
      io_context_t& get_io_context();
    private:
#if BOOST_VERSION <= 106501
      using work_t = boost::asio::io_service::work;
#else
      using work_t = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;
#endif
    private:
      io_context_t m_io_context;
      work_t m_work;
    };

  } /* namespace details */

} /* namespace net */
