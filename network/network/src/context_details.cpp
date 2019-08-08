#include "context_details.h"

namespace net {

  namespace details {

      void context_t::run() {
        m_io_context.run();
      }

      void context_t::stop() {
        m_io_context.stop();
      }

      context_t::io_context_t& context_t::get_io_context() {
        return m_io_context;
      }

  } /* namespace details */

} /* namespace net */
