#pragma once
#include <librdkafka/rdkafkacpp.h>
#include <avro/Generic.hh>
#include <spdlog/spdlog.h>

#include <consumer/NasdaqKafkaAvroConsumer.h>


/**
 * \defgroup ncdsclient ncdsclient
 * Contains the NCDSClient class, the client class used to access Nasdaq's market data.
 * @{
 */


/** @brief A client class to access Nasdaq's market data.
    */
namespace ncds {

  class NCDSClient {
  private:
    NasdaqKafkaAvroConsumer nasdaq_kafka_avro_consumer;
    std::shared_ptr<spdlog::logger> logger;
    int timeout;
  public:
    NCDSClient(RdKafka::Conf *kafka_cfg, std::unordered_map<std::string, std::string> &security_cfg);

    /**
     * Method produces a topics list from the NasdaqKafkaAvroConsumer instance.
     * @return a list of eligible topics/streams for the client
     */
    std::set<std::string> list_topics_for_the_client();

    /**
     * Method takes in a topic and retrieves the schema from the consumer instance.
     * @param topic Topic/Stream name
     * @return the Kafka schema name for the given topic
     */
    avro::ValidSchema get_schema(const std::string &topic);

    /**
     * Retrieves the Apache Kafka consumer. The consumer will start consuming at either the
     * earliest or latest offset, depending on the value set for auto.offset.reset in kafka_cfg.
     * @param topic: Topic/Stream name
     * @return Nasdaq's market data Kafka consumer
     */
    std::unique_ptr<RdKafka::KafkaConsumer> NCDSKafkaConsumer(const std::string &topic);

    /**
     * Retrieves the apache kafka consumer after seeking to the given timestamp.
     * @param topic Topic/Stream name
     * @param timestamp timestamp in milliseconds since the UNIX epoch
     * @return Nasdaq's market data Kafka consumer
     */
    std::unique_ptr<RdKafka::KafkaConsumer> NCDSKafkaConsumer(const std::string &topic, long timestamp);

    /**
     * Retrieves the given num_messages messages from the given topic. If there are not enough messages in the
     * topic, then all the messages in the topic will be returned.
     *
     * @param topic_name Topic/Stream name
     * @param num_messages the number of messages to return
     * @return A vector of messages from the given topic containing num_messages messages
     */
    std::vector<avro::GenericRecord> top_messages(const std::string &topic_name, int num_messages);

    /**
     * Retrieves the given num_messages messages from the given topic after seeking to the given timestamp.
     * If there are not enough messages in the topic, then all the messages in the topic will be returned.
     * @param topic_name Topic/Stream name
     * @param timestamp timestamp in milliseconds since the UNIX epoch
     * @param num_messages the number of messages to consume and return
     * @return A vector of messages from the given topic containing num_messages messages
     */
    std::vector<avro::GenericRecord> top_messages(const std::string &topic_name, long timestamp, int num_messages);

    /**
     * If all_messages is True, prints out all messages with given message name and topic. Otherwise, retrieves
     * the first message from the topic with the given message name.
     * @param topic_name name of topic we want to get a sample message for
     * @param message_name name of the message, retrieved from the schema
     * @param all_messages True if function should query for all sample messages, False if function should query for just one
     * @return a sample message with the given message name
     * @throw an Exception if no sample message is found with the given message name
     */
    avro::GenericRecord get_sample_messages(const std::string &topic_name, const std::string &message_name, bool all_messages);

    /**
     * Checks if there is a final sequence number for this stream signaling the end of the data.
     * @param consumer the Kafka Consumer
     * @param topic_name the name of the topic/stream the consumer is assigned to
     * @return a boolean if the end of data has been reached.
     */
    bool end_of_data(RdKafka::KafkaConsumer *consumer, const std::string &topic_name);
  };
} // namespace ncds

/**@}*/
