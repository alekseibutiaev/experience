
#include <location.h>

#include <error.h>

#include "types.h"

#include "event.h"

namespace nasdaq {

  namespace acc {

    event_t::event_t(const error_t& error)
        : m_error(error)
        , m_next(0) {
    }

    void event_t::set_next(RdKafka::EventCb* next) {
      m_next = next;
    }

    void event_t::event_cb(RdKafka::Event& event) {
      static const notify_t notify[] = { &error_t::error, &error_t::error, &error_t::error,
        &error_t::error, &error_t::warning, &error_t::info, &error_t::info, &error_t::debug };
      (m_error.*notify[event.severity()])(" " + event.fac() + " " + event.str() + __FILE_STR__);
      if(m_next)
        m_next->event_cb(event);
    }

  } /* namespace acc */

} /* namespace nasdaq */

