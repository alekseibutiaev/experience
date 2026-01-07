#pragma once

#include <memory>
#include <map>
#include <string>
#include <vector>
#include <thread>

#include "acc_types.h"

namespace nasdaq {

  class error_t;

  namespace acc {

    class event_t;
    class config_t;
    class queue_control_t;

    class consumer_t {
    public:
      using strings_t = std::vector<std::string>;
      using topic_sq_t = std::map<std::string, std::size_t>;
      using execute_t = std::function<void(std::function<void()>)>;
      using process_t = std::function<void(const std::string&, const void*, const std::size_t&,
        const std::size_t&, const time_point_t&)>;
    public:
      consumer_t(const config_t& config, const get_property_t& get_property,
        const execute_t& executer, const process_t& process, const error_t& error);
      void start(const strings_t& topics);
      void stop();
    private:
      using auth_ptr = std::shared_ptr<RdKafka::OAuthBearerTokenRefreshCb>;
      using topic_partition_ptr = std::shared_ptr<RdKafka::TopicPartition>;
      using consumer_ptr = std::shared_ptr<RdKafka::KafkaConsumer>;
      using config_prt = std::shared_ptr<config_t>;
      using event_ptr = std::shared_ptr<event_t>;
      using msg_ptr = std::shared_ptr<RdKafka::Message>;
    private:
      void consumer_process();
      //void queue_process(queue_control_t& value);
    private:
      const error_t& m_error;
      config_prt m_config;
      const get_property_t& m_get_property;
      const execute_t m_execute;
      const process_t m_process;
      auth_ptr m_auth;
      event_ptr m_event;
      bool m_start;
      topic_sq_t m_topic_sq;
      std::vector<topic_partition_ptr> m_topic_partitions;
      consumer_ptr m_consumer;
      std::thread m_consumer_tread;
    };

  } /* namespace acc */

} /* namespace nasdaq */
