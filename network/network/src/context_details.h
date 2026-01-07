#pragma once

#include <boost/asio.hpp>
#include <boost/version.hpp>

#include "nettype_details.h"

#include "context.h"

namespace net {

  namespace details {

    class context_t : public net::context_t {
    public:
      context_t(const error_handle_t& handelr);
      void run() override;
      std::size_t run_one(error_code_t& err) override;
      void stop() override;
      const error_handle_t& get_error_handle() override;
      io_context_t& get_io_context();
    private:
#if BOOST_VERSION < 106600
      using work_t = boost::asio::io_service::work;
#else
      using work_t = boost::asio::executor_work_guard<boost::asio::io_context::executor_type>;
#endif
    private:
      const error_handle_t m_handelr;
      io_context_t m_io_context;
      work_t m_work;
    };

  } /* namespace details */

} /* namespace net */
