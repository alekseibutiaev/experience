#include <cassert>
#include <string>
#include <fstream>

#include <spdlog/spdlog.h>

#include <librdkafka/rdkafkacpp.h>

#include <avro/ValidSchema.hh>
#include <avro/Compiler.hh>


#include "internal/ReadSchemaTopic.h"
#include "internal/utils/SeekToMidnight.h"
#include "internal/utils/AuthenticationConfigLoader.h"
#include "internal/Logging.h"
#include "internal/utils/FindResources.h"
#include "internal/utils/KafkaConfigLoader.h"
#include "AvroDeserializer.h"

//constructor
ReadSchemaTopic::ReadSchemaTopic()
{
  control_schema_name = "control";
  logger = spdlog::get(LOGGER);
  timeout = get_timeout_config();
}

avro::ValidSchema ReadSchemaTopic::read_schema(const std::string &topic)
{
    //logger->debug( "Starting read_schema";
    AuthenticationConfigLoader auth_config_loader;
    RdKafka::Conf *conf = this->kafka_props;
    std::string group_id = "Control-" + auth_config_loader.get_client_id(this->auth_props);
    std::unique_ptr<RdKafka::KafkaConsumer> schema_consumer = ReadSchemaTopic::get_consumer(group_id);
    //schema_consumer->consume(0);

    std::vector<std::string> control_schema_topic;
    control_schema_topic.push_back(control_schema_name);
    schema_consumer->subscribe(control_schema_topic);

    logger->debug("Before getting resource path");
    std::string path = get_resource_path();
    logger->debug("After getting resource path");

    std::ifstream in(path + "ControlMessageSchema.avsc");
    if (!in.good()) {
        throw std::runtime_error("Could not open file: ControlMessageSchema.avsc");
    }
    avro::ValidSchema control_message_schema;
    avro::compileJsonSchema(in, control_message_schema);

    logger->debug( "Succesfully parsed control msg schema");

    ncds::DeserializeMsg consume(control_message_schema);

    avro::GenericRecord *latest_record;

    avro::ValidSchema message_schema;

    bool message_schema_found = false;

    std::vector<avro::GenericRecord> all_records;
    while (true)
    {
//        logger->debug( "Before consuming control topic";
        std::unique_ptr<RdKafka::Message> msg = std::unique_ptr<RdKafka::Message>(schema_consumer->consume(this->timeout));

        if (msg->err() != 0)
        {

            logger->debug( "Error: {}", err2str(msg->err()));
            break;
        }

        avro::GenericRecord record = consume.deserialize_msg(*msg);
        if (record.hasField("name"))
        {
            avro::GenericDatum record_name = record.field("name");
            assert(record_name.type() == avro::AVRO_STRING);

            if (record_name.value<std::string>() == topic)
            {
                if (!all_records.empty())
                {
                    all_records.pop_back();
                }
                all_records.push_back(record);
            }
        }
    }
    schema_consumer->close();

    logger->debug( "Consumed all records in control topic");

    latest_record = &all_records.back();

    if (!all_records.empty() && latest_record->hasField("schema"))
    {
        avro::GenericDatum message_schema_datum = latest_record->field("schema");
        assert(message_schema_datum.type() == avro::AVRO_STRING);
        message_schema = avro::compileJsonSchemaFromString(message_schema_datum.value<std::string>());
        message_schema_found = true;
    }

    if (!message_schema_found)
    {
//        assert(false);
        logger->warn("WARNING: Using the Old Schema! It might not be the latest schema.");
        message_schema = ReadSchemaTopic::internal_schema(topic);
    }

//    logger->debug( "Json Schema: " << message_schema.toJson();
    return message_schema;
}

void ReadSchemaTopic::set_kafka_props(RdKafka::Conf *props)
{
    this->kafka_props = props;
}

void ReadSchemaTopic::set_auth_props(std::unordered_map<std::string, std::string> &props)
{
    this->auth_props = props;
}

std::set<std::string> ReadSchemaTopic::get_topics()
{
    std::set<std::string> topics;
    AuthenticationConfigLoader auth_config_loader;
    std::string group_id = "Control-" + auth_config_loader.get_client_id(this->auth_props);
    auto schema_consumer = ReadSchemaTopic::get_consumer(group_id);

    std::vector<std::string> control_topic;
    control_topic.push_back(control_schema_name);
    schema_consumer->subscribe(control_topic);

    std::ifstream in(get_resource_path() + "ControlMessageSchema.avsc");
    if (!in.good()) {
        throw std::runtime_error("Could not open file: ControlMessageSchema.avsc");
    }
    avro::ValidSchema control_message_schema;
    avro::compileJsonSchema(in, control_message_schema);

    ncds::DeserializeMsg consume(control_message_schema);

    while (true)
    {
        std::unique_ptr<RdKafka::Message> msg = std::unique_ptr<RdKafka::Message>(schema_consumer->consume(this->timeout));
        if (msg->err() != 0)
        {
	    logger->debug( "No messages found, breaking out of while loop");
            // break if there is any error code returned
            break;
        }

        logger->debug( "About to deserialize control msg");
        avro::GenericRecord record = consume.deserialize_msg(*msg);
        if (record.hasField("name"))
        {
            avro::GenericDatum record_name = record.field("name");
            assert(record_name.type() == avro::AVRO_STRING);
            std::string topic_name = record_name.value<std::string>();
            topics.insert(topic_name);
        }
    }

    schema_consumer->close();
    return topics;
}

std::unique_ptr<RdKafka::KafkaConsumer> ReadSchemaTopic::get_consumer(const std::string &client_id)
{
    std::string errstr;
    kafka_props->set("auto.offset.reset", "earliest", errstr);
    kafka_props->set("group.id", client_id, errstr);
    errstr = "";
    std::unique_ptr<RdKafka::KafkaConsumer> schema_consumer = std::unique_ptr<RdKafka::KafkaConsumer>(RdKafka::KafkaConsumer::create(this->kafka_props, errstr));
    if (!schema_consumer.get()) {
        throw std::runtime_error("Failed to create Control topic consumer: " + errstr);
    }

    std::vector<RdKafka::TopicPartition *> partitions;
    std::unique_ptr<RdKafka::TopicPartition> topic_partition = std::unique_ptr<RdKafka::TopicPartition>(RdKafka::TopicPartition::create(control_schema_name, 0, RdKafka::Topic::OFFSET_BEGINNING));
    partitions.push_back(topic_partition.get());

    RdKafka::ErrorCode assign_error = schema_consumer->assign(partitions);
    logger->debug( "assign error: {}", err2str(assign_error));

    std::unique_ptr<RdKafka::Message> msg = std::unique_ptr<RdKafka::Message>(schema_consumer->consume(0));
    logger->debug( "consume error: {}", err2str(msg->err()));

    //    RdKafka::ErrorCode position_error = schema_consumer->position(partitions);
    //    logger->debug( "position set offsets to: " << topic_partition->offset();
    //    logger->debug( "POSITION ERROR IS: " << err2str(position_error);

    logger->debug( "seeking to midnight");
    seek_to_midnight_at_past_day(schema_consumer.get(), topic_partition.get(), 7);

    return schema_consumer;
}

avro::ValidSchema ReadSchemaTopic::internal_schema(const std::string &topic)
{
    avro::ValidSchema topic_schema;
    std::ifstream in(get_resource_path() + topic + ".avsc");
    avro::compileJsonSchema(in, topic_schema);
    return topic_schema;
}
