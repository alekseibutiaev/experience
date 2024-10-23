#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <chrono>


#include <stdexcept>

#include <librdkafka/rdkafka.h>
#include <librdkafka/rdkafkacpp.h>

#include <config.h>
#include <consumer.h>

#include "tools.h"
#include "oauthbearer.h"
#include "event.h"

namespace {

  kf::config_t clone_config(const kf::config_t& config, const kf::error_t& notify) {
    if(kf::config_t::e_global != config.get_type())
      throw(std::runtime_error("config is not a global"));
    return config.clone(notify);
  }

  long long get_timestamp_at_midnight(int num_days_ago) {
    const auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch();
    long long res = ((now - std::chrono::hours(24) * num_days_ago) - now % std::chrono::hours(24)).count();
    return res;
  }

  void seek_to_midnight_at_past_day(RdKafka::KafkaConsumer *kafka_consumer,
      RdKafka::TopicPartition *topic_partition, int num_days_ago) {
    std::vector<RdKafka::TopicPartition*> partitions;
    topic_partition->set_offset(get_timestamp_at_midnight(num_days_ago));
    partitions.push_back(topic_partition);
    RdKafka::ErrorCode error_code = kafka_consumer->offsetsForTimes(partitions, 10000);
    if (error_code == RdKafka::ERR_NO_ERROR) {
      kafka_consumer->seek(*topic_partition, 10000);
    } else {
      topic_partition->set_offset(RdKafka::Topic::OFFSET_BEGINNING);
      kafka_consumer->seek(*topic_partition, 10000);
    }
    int64_t partition_offset = topic_partition->offset();
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

  void consumer_t::logger(const struct rd_kafka_s* rk, int level, const char* fac, const char* buf) {
    if(level == 7)
      return;
    std::cout << "Pounter: 0x" << std::hex << rk << std::dec << " level " << level << " " << fac <<
      " " << buf << std::endl;
  }

} /* namespace kf */
