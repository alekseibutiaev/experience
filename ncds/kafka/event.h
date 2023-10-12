#pragma once

#include <librdkafka/rdkafkacpp.h>

namespace kf {

  class event_t : public RdKafka::EventCb {
    void event_cb(RdKafka::Event &event) override;
  };

} /* namespace kf */
