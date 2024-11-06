#pragma once

#include <mutex>
#include <memory>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <condition_variable>
#include <functional>

#include "cache_queue.hpp"

#include "types.h"

struct rd_kafka_s;

namespace kf {

  class error_t;
  class event_t;
  class config_t;

  class consumer_t {
  public:
    using strings_t = std::vector<std::string>;
    using process_t = std::function<void(const time_point_t&, const std::string&, const void*, const std::size_t)>;
  public:
    consumer_t(const config_t& config, const get_property_t& get_property, const error_t& err);
    void start(const strings_t& topics, const process_t& process);
    void stop();
  private:
    using auth_ptr = std::shared_ptr<RdKafka::OAuthBearerTokenRefreshCb>;
    using event_ptr = std::shared_ptr<event_t>;
    using topic_partition_ptr = std::shared_ptr<RdKafka::TopicPartition>;
    using consumer_ptr = std::shared_ptr<RdKafka::KafkaConsumer>;
    using msg_ptr = std::shared_ptr<RdKafka::Message>;
    using queue_element_t = std::function<void()>;
    using queue_t = tools::cache_queue_t<queue_element_t>;
  private:
    void consumer_process(const process_t& process);
    void queue_process();
    void msg_process(const process_t&, const time_point_t, const msg_ptr);
  private:
    config_t m_config;
    const get_property_t& m_get_property;
    const error_t& m_error;
    auth_ptr m_auth;
    event_ptr m_event;
    std::vector<topic_partition_ptr> m_topic_partitions;
    consumer_ptr m_consumer;
    queue_t m_queue;
    bool m_start;
    std::thread m_consumer_tread;
    std::mutex m_queue_mutex;
    std::condition_variable m_queue_cv;    
//    std::thread m_queue_tread;
  };

} /* namespace kf */
