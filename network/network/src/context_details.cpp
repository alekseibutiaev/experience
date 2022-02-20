#include "context_details.h"

namespace net {

  namespace details {

    context_t::context_t(const error_handle_t& handelr)
      : m_handelr(handelr)
#if BOOST_VERSION <= 106501
      , m_work(m_io_context) {
#else
      , m_work(boost::asio::make_work_guard(m_io_context)) {
#endif
      }

    void context_t::run() {
      m_io_context.run();
    }

    std::size_t context_t::run_one(error_code_t& err) {
      return m_io_context.run_one(err);
    }

    void context_t::stop() {
#if BOOST_VERSION > 106501
      m_work.reset();
#endif
      m_io_context.stop();
    }

    const error_handle_t& context_t::get_error_handle() {
      return m_handelr;
    }

    io_context_t& context_t::get_io_context() {
      return m_io_context;
    }

  } /* namespace details */

  context_ptr context_t::create(const error_handle_t& handelr) {
    return context_ptr(new details::context_t(handelr));
  }

} /* namespace net */
