//
// Created by Jennifer Wang on 7/21/21.
//
#pragma once

namespace RdKafka {
  class KafkaConsumer;
  class TopicPartition;
}

int get_timestamp_at_midnight(int num_days_ago);

void seek_to_midnight_at_past_day(RdKafka::KafkaConsumer* kafka_consumer,
    RdKafka::TopicPartition* topic_partition, int num_days_ago);
