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

#include "print_records.h"
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
    std::string err;
    m_consumer.reset(RdKafka::KafkaConsumer::create(m_config.get_config(), err));
    std::vector<RdKafka::TopicPartition*> partitions;
    for(const auto& it : topics) {
      partitions.push_back(RdKafka::TopicPartition::create(it, 0, RdKafka::Topic::OFFSET_END));
      m_topic_partitions.push_back(topic_partition_ptr(partitions.back()));
    }
    m_consumer->assign(partitions);

    std::string offset;
    m_config.get("auto.offset.reset", offset);
    std::cout << offset << std::endl;

    if (offset == "earliest" || offset == "smallest" || offset == "beginning") {
      for(auto& it : m_topic_partitions)
        seek_to_midnight_at_past_day(m_consumer.get(), it.get(), 0);
    }

    for(;;) {
      std::unique_ptr<RdKafka::Message> msg = std::unique_ptr<RdKafka::Message>(m_consumer->consume(10));
      if(0 >= msg->payload())
        continue;
      process(msg->topic_name(), msg->payload(), msg->len());
    }
  }


  void consumer_t::control(const process_f& process) {
    std::string err;
    m_control.reset(RdKafka::KafkaConsumer::create(m_config.get_config(), err));
    std::vector<RdKafka::TopicPartition*> partitions;
    std::unique_ptr<RdKafka::TopicPartition> prt(RdKafka::TopicPartition::create("control", 0, RdKafka::Topic::OFFSET_END));
    partitions.push_back(prt.get());
    seek_to_midnight_at_past_day(m_control.get(), prt.get(), 1);
    m_control->assign(partitions);
    for(;;) {
      std::unique_ptr<RdKafka::Message> msg = std::unique_ptr<RdKafka::Message>(m_control->consume(10000));
      if(0 >= msg->payload())
        continue;
      process(msg->topic_name(), msg->payload(), msg->len());
    }
  }

  void consumer_t::logger(const struct rd_kafka_s* rk, int level, const char* fac, const char* buf) {
    if(level == 7)
      return;
    std::cout << "Pounter: 0x" << std::hex << rk << std::dec << " level " << level << " " << fac <<
      " " << buf << std::endl;
  }

} /* namespace kf */
