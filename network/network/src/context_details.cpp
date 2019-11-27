#include "context_details.h"

namespace net {

  namespace details {

    context_t::context_t()
#if BOOST_VERSION <= 106501
      : m_work(m_io_context) {
#else
      : m_work(boost::asio::make_work_guard(m_io_context)) {
#endif
      }

    void context_t::run() {
      m_io_context.run();
    }

    void context_t::stop() {
#if BOOST_VERSION > 106501
      m_work.reset();
#endif
      m_io_context.stop();
    }

    io_context_t& context_t::get_io_context() {
      return m_io_context;
    }

  } /* namespace details */

  context_ptr context_t::create() {
    return context_ptr(new details::context_t());
  }

} /* namespace net */
