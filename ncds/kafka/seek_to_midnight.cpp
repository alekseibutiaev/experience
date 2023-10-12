
#include <memory>
#include <chrono>

#include <spdlog/spdlog.h>

#include <librdkafka/rdkafkacpp.h>

#include "internal/utils/SeekToMidnight.h"

int get_timestamp_at_midnight(int num_days_ago) {
  auto days_past = std::chrono::system_clock::now()-std::chrono::hours(24*num_days_ago);
  time_t tnow = std::chrono::system_clock::to_time_t(days_past);
  tm *date = std::localtime(&tnow);
  date->tm_hour = 0;
  date->tm_min = 0;
  date->tm_sec = 0;
  std::chrono::system_clock::time_point midnight = std::chrono::system_clock::from_time_t(std::mktime(date));
  auto midnight_ms = std::chrono::time_point_cast<std::chrono::milliseconds>(midnight);
  auto value = midnight_ms.time_since_epoch();
  long midnight_timestamp = value.count();
  return midnight_timestamp;
}

void seek_to_midnight_at_past_day(RdKafka::KafkaConsumer *kafka_consumer,
    RdKafka::TopicPartition *topic_partition, int num_days_ago) {
  std::vector<RdKafka::TopicPartition*> partitions;
  topic_partition->set_offset(get_timestamp_at_midnight(num_days_ago));
  partitions.push_back(topic_partition);

  RdKafka::ErrorCode error_code = kafka_consumer->offsetsForTimes(partitions, 10000);

  int64_t partition_offset = topic_partition->offset();

  if (error_code == RdKafka::ERR_NO_ERROR) {
//  topic_partition->set_offset(RdKafka::Topic::OFFSET_BEGINNING);
    kafka_consumer->seek(*topic_partition, 10000);
  } else {
    topic_partition->set_offset(RdKafka::Topic::OFFSET_BEGINNING);
    kafka_consumer->seek(*topic_partition, 10000);
  }
}


