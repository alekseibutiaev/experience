
#include <memory>
#include <chrono>

#include <spdlog/spdlog.h>

#include <librdkafka/rdkafkacpp.h>

#include "internal/Logging.h"
#include "internal/utils/SeekToMidnight.h"

int get_timestamp_at_midnight(int num_days_ago) {
  auto logger = spdlog::get(LOGGER);
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
  logger->debug("ms: MIDNIGHT TIMESTAMP: {} ", midnight_timestamp);
  return midnight_timestamp;
}

void seek_to_midnight_at_past_day(RdKafka::KafkaConsumer *kafka_consumer,
    RdKafka::TopicPartition *topic_partition, int num_days_ago) {
  auto logger = spdlog::get(LOGGER);
  std::vector<RdKafka::TopicPartition*> partitions;
  topic_partition->set_offset(get_timestamp_at_midnight(num_days_ago));
  partitions.push_back(topic_partition);
  logger->debug( "Setting partition offset");

  RdKafka::ErrorCode error_code = kafka_consumer->offsetsForTimes(partitions, 10000);

  int64_t partition_offset = topic_partition->offset();
  logger->debug( "partition offset is: {}",partition_offset);

  if (error_code == RdKafka::ERR_NO_ERROR) {
//  topic_partition->set_offset(RdKafka::Topic::OFFSET_BEGINNING);
    logger->debug( "seeking to topic partition");
    kafka_consumer->seek(*topic_partition, 10000);
  } else {
    logger->info( "Seek to midnight failed - Seeking to OFFSET_BEGINNING instead. ", err2str(error_code));
    topic_partition->set_offset(RdKafka::Topic::OFFSET_BEGINNING);
    kafka_consumer->seek(*topic_partition, 10000);
  }
}


