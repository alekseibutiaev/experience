#pragma once

#include <memory>
#include <string>
#include <vector>
#include <functional>

#include <types.h>

struct rd_kafka_s;

namespace kf {

  class error_t;
  class event_t;
  class config_t;

  class consumer_t {
  public:
    using process_f = std::function<void(const std::string&, const void*, const std::size_t)>;
    using strings_t = std::vector<std::string>;
  public:
    consumer_t(const config_t& config, const get_property_t& get_property, const error_t& err);
    void consume(const strings_t topics, const process_f& process);
  private:
    using auth_ptr = std::shared_ptr<RdKafka::OAuthBearerTokenRefreshCb>;
    using event_ptr = std::shared_ptr<event_t>;
    using topic_partition_ptr = std::shared_ptr<RdKafka::TopicPartition>;
    using consumer_ptr = std::shared_ptr<RdKafka::KafkaConsumer>;
  private:
    config_t m_config;
    const get_property_t& m_get_property;
    const error_t& m_error;
    auth_ptr m_auth;
    event_ptr m_event;
    std::vector<topic_partition_ptr> m_topic_partitions;
    consumer_ptr m_consumer;
  };

} /* namespace kf */
