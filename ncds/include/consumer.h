#pragma once

#include <memory>

#include <types.h>

struct rd_kafka_s;

namespace kf {

  class config_t;

  class consumer_t {
  public:
    consumer_t(const config_t& config, const get_property_t& get_property, const error_t& notify);
    void test();
  private:
    using auth_ptr = std::shared_ptr<RdKafka::OAuthBearerTokenRefreshCb>;
    using topic_partition_ptr = std::shared_ptr<RdKafka::TopicPartition>;
    using consumer_ptr = std::shared_ptr<RdKafka::KafkaConsumer>;
  private:
    static void logger(const struct rd_kafka_s* rk, int level, const char* fac, const char* buf);
  private:
    config_t m_config;
    const get_property_t& m_get_property;
    auth_ptr m_auth;
    topic_partition_ptr m_topic_partition;
    consumer_ptr m_consumer;
  };

} /* namespace kf */
