#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include <stdexcept>

#include <librdkafka/rdkafka.h>
#include <librdkafka/rdkafkacpp.h>

#include <config.h>
#include <consumer.h>
#include <internal/utils/SeekToMidnight.h>

#include "oauthbearer.h"
#include "event.h"

namespace {

  kf::config_t clone_config(const kf::config_t& config, const kf::error_t& notify) {
    if(kf::config_t::e_global != config.get_type())
      throw(std::runtime_error("config is not a global"));
    return config.clone(notify);
  }

} /* namespace */

namespace kf {

  consumer_t::consumer_t(const config_t& config, const get_property_t& get_property, const error_t& notify)
      : m_config(clone_config(config, notify))
      , m_get_property(get_property)
      , m_auth(std::make_shared<oauthbearer_t>(get_property))
      , m_event(std::make_shared<event_t>()) {
    config.print();
    std::cout << "conf" << std::endl;
    m_config.set(m_auth.get(), notify);
//    m_config.set(m_event.get(), notify);
    rd_kafka_conf_set_log_cb(m_config.get_config()->c_ptr_global(), logger);
    m_config.print();
  }


  void consumer_t::consume(strings_t topics, const process_f& process) {
    static std::size_t count = 0;
    if(const auto topic = m_get_property("topic")) {
      std::string err;
      m_consumer.reset(RdKafka::KafkaConsumer::create(m_config.get_config(), err));
      std::vector<RdKafka::TopicPartition*> part;
      for(const auto& it : topics) {
        part.push_back(RdKafka::TopicPartition::create(it, 0, RdKafka::Topic::OFFSET_END));
        m_topic_partitions.push_back(topic_partition_ptr(part.back()));
      }
      m_consumer->assign(part);
      std::string offset;
      m_config.get("auto.offset.reset", offset);
      std::cout << offset << std::endl;
      if (offset == "earliest" || offset == "smallest" || offset == "beginning") {
        for(auto& it : m_topic_partitions)
          seek_to_midnight_at_past_day(m_consumer.get(), it.get(), 0);
      }
      for(;;) {
        std::unique_ptr<RdKafka::Message> msg = std::unique_ptr<RdKafka::Message>(m_consumer->consume(10000));
        if(0 >= msg->payload())
          continue;
        process(msg->topic_name(), msg->payload(), msg->len());
      }
    }
    else {
      std::cout << "topic unuavaqilable: " << std::endl;
    }
  }

  void consumer_t::logger(const struct rd_kafka_s* rk, int level, const char* fac, const char* buf) {
    if(level == 7)
      return;
    std::cout << "Pounter: 0x" << std::hex << rk << std::dec << " level " << level << " " << fac <<
      " " << buf << std::endl;
  }

} /* namespace kf */
