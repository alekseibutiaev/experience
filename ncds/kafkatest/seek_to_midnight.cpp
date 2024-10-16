
#include <memory>
#include <chrono>

#include <librdkafka/rdkafkacpp.h>

#include "seek_to_midnight.h"

int get_timestamp_at_midnight(int num_days_ago) {
  const auto now = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()).time_since_epoch();
  return ((now - std::chrono::hours(24) * num_days_ago) - now % std::chrono::hours(24)).count();
}

void seek_to_midnight_at_past_day(RdKafka::KafkaConsumer *kafka_consumer,
    RdKafka::TopicPartition *topic_partition, int num_days_ago) {
  std::vector<RdKafka::TopicPartition*> partitions;
  topic_partition->set_offset(get_timestamp_at_midnight(num_days_ago));
  partitions.push_back(topic_partition);

  RdKafka::ErrorCode error_code = kafka_consumer->offsetsForTimes(partitions, 10000);

  if (error_code == RdKafka::ERR_NO_ERROR) {
//  topic_partition->set_offset(RdKafka::Topic::OFFSET_BEGINNING);
    kafka_consumer->seek(*topic_partition, 10000);
  } else {
    topic_partition->set_offset(RdKafka::Topic::OFFSET_BEGINNING);
    kafka_consumer->seek(*topic_partition, 10000);
  }

  int64_t partition_offset = topic_partition->offset();

}


