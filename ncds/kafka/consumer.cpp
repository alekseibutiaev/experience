#include <iostream>
#include <stdexcept>

#include <librdkafka/rdkafka.h>
#include <librdkafka/rdkafkacpp.h>

#include <config.h>
#include <consumer.h>

#include "oauthbearer.h"

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
      , m_auth(std::make_shared<oauthbearer_t>(get_property)) {
    m_config.set(m_auth.get(), notify);
    rd_kafka_conf_set_log_cb(m_config.get_config()->c_ptr_global(), logger);
  }

  void consumer_t::test() {
    if(const auto topic = m_get_property("topic")) {
      std::string err = *topic + ".stream";
      m_topic_partition.reset(RdKafka::TopicPartition::create(*topic + ".stream", 0, RdKafka::Topic::OFFSET_END));
      m_consumer.reset(RdKafka::KafkaConsumer::create(m_config.get_config(), err));
      m_consumer->assign({m_topic_partition.get()});

    }

  }

  void consumer_t::logger(const struct rd_kafka_s* rk, int level, const char* fac, const char* buf) {
    std::cout << "Pounter: 0x" << std::hex << rk << std::dec << " level " << level << " " << fac <<
      " " << buf << std::endl;
  }

} /* namespace kf */
