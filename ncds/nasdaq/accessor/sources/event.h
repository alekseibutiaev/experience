#pragma once

#include <string>

#include <librdkafka/rdkafkacpp.h>

namespace nasdaq {

  class error_t;

  namespace acc {

    class event_t : public RdKafka::EventCb {
    public:
      event_t(const error_t& error);
      void set_next(RdKafka::EventCb* next = 0);
    private:
      using notify_t = void(error_t::*)(const std::string&) const;
    private:
      void event_cb(RdKafka::Event &event) override;
    private:
      const error_t& m_error;
      RdKafka::EventCb* m_next;
    };

  } /* namespace acc */

} /* namespace nasdaq */
