
#include <mutex>
#include <list>
#include <chrono>
#include <fstream>
#include <utility>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <condition_variable>

#include <librdkafka/rdkafka.h>
#include <librdkafka/rdkafkacpp.h>

#include "../config.h"
#include "tools.h"
#include "error.h"
#include "event.h"
#include "location.h"
#include "oauthbearer.h"

#include "accessor/consumer.h"

namespace {

  using first_msg_t = std::pair<bool, bool>;

  nasdaq::acc::config_t clone_config(const nasdaq::acc::config_t& config, const nasdaq::error_t& notify) {
    if(nasdaq::acc::config_t::e_global != config.get_type())
      throw(std::runtime_error("config is not a global"));
    return config.clone(notify);
  }

  long long get_timestamp_at_midnight(int num_days_ago) {
    const auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch();
    long long res = ((now - std::chrono::hours(24) * num_days_ago) - now % std::chrono::hours(24)).count();
    return res;
  }

  void seek_to_midnight_at_past_day(RdKafka::KafkaConsumer* kafka_consumer,
      RdKafka::TopicPartition* topic_partition, int num_days_ago) {
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
    /*int64_t partition_offset = */topic_partition->offset();
  }

  void update_logger(nasdaq::acc::config_t& config, nasdaq::acc::event_t* event,
      const nasdaq::error_t& error) {
    if(RdKafka::EventCb* current = config.get(static_cast<RdKafka::EventCb*>(0), error))
      event->set_next(current);
    config.set(event, error);
  }

  void check_first_message_for_topics(first_msg_t& flags, const nasdaq::acc::consumer_t::strings_t& request,
      nasdaq::acc::consumer_t::strings_t& current, const std::string& topic) {
    for(auto it = std::find(current.begin(), current.end(), topic); (flags.second = it == current.end());) {
      current.push_back(topic);
      flags.first = request.size() != current.size();
    }
  }

} /* namespace */

namespace nasdaq {

  namespace acc {

    class queue_control_t {
    public:
      using queue_element_t = std::function<void()>;
      using queue_t = std::list<queue_element_t>;
    public:
      queue_t m_queue;
      std::mutex m_mutex;
      std::condition_variable m_cv;    
    };

    consumer_t::consumer_t(const config_t& config, const get_property_t& get_property,
        const execute_t& execute, const process_t& process, const error_t& error)
        : m_error(error)
        , m_config(std::make_shared<config_prt::element_type>(clone_config(config, m_error)))
        , m_get_property(get_property)
        , m_execute(execute)
        , m_process(process)
        , m_auth(std::make_shared<oauthbearer_t>(m_get_property))
        , m_event(std::make_shared<event_t>(m_error))
        , m_start(false) {
      update_logger(*m_config, m_event.get(), m_error);
      m_config->set(m_auth.get(), m_error);
    }

    void consumer_t::start(const strings_t& topics) {
      if(m_consumer_tread.joinable())
        return;
      m_first_msg[0] = topics;
      std::string err;
      if(m_consumer = consumer_ptr(RdKafka::KafkaConsumer::create(m_config->get_config(), err))) {
        std::vector<RdKafka::TopicPartition*> partitions;
        for(const auto& it : topics) {
          partitions.push_back(RdKafka::TopicPartition::create(it, 0, RdKafka::Topic::OFFSET_END));
          m_topic_partitions.push_back(topic_partition_ptr(partitions.back()));
        }
        m_consumer->assign(partitions);

        std::string offset;
        m_config->get("auto.offset.reset", offset, m_error);

        if (offset == "earliest" || offset == "smallest" || offset == "beginning")
          for(auto& it : m_topic_partitions)
            seek_to_midnight_at_past_day(m_consumer.get(), it.get(), 0);

        m_start = true;
        m_consumer_tread = std::thread(&consumer_t::consumer_process, this);
      }
      else
        m_error.error(err + __FILE_STR__);
    }

    void consumer_t::stop() {
      if(m_consumer_tread.joinable()) {
        m_start = false;
        m_consumer_tread.join();
        m_consumer->close();
      }
    }

    void consumer_t::consumer_process() {
      try {
        first_msg_t flags = {true, true};
        for(;m_start;) {
          msg_ptr msg(m_consumer->consume(1000));
          if(!msg->payload())
            continue;
          if(flags.first)
            check_first_message_for_topics(flags, m_first_msg[0], m_first_msg[1], msg->topic_name());
          auto ts = flags.second ? time_point_t() : clock_t::now();
          m_execute([this, msg, ts]() {
              m_process(ts, msg->topic_name(), msg->payload(), msg->len());});
        }
      }
      catch(const std::exception& e) {
        m_error.error(e.what() + __FILE_STR__);
      }
    }

  } /* namespace acc */

} /* namespace nasdaq */
