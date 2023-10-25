#include <string>
#include <memory>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include <nlohmann/json.hpp>

#include <librdkafka/rdkafkacpp.h>

#include <avro/ValidSchema.hh>
#include <avro/Compiler.hh>

#include <internal/utils/SeekToMidnight.h>

#include <print_records.h>


#include <config.h>

namespace {

  avro::ValidSchema load(const std::string& file) {
    std::ifstream ifs(file.c_str());
    if(!ifs.good())
      throw(std::runtime_error("can`t open file: " + file));
    std::string error;
    avro::ValidSchema schema;
    avro::compileJsonSchema(ifs, schema, error);
    return schema;
  }

  class read_json_t {
  public:
    read_json_t(const nlohmann::json& json)
      : m_json(json) {
    }
    kf::string_try_t operator()(const std::string& val) const {
      return  m_json.contains(val) ? m_json[val].is_string() ?
        kf::string_try_t(m_json[val]) : m_json[val].dump() : kf::string_try_t();
    }
    
  private:
    const nlohmann::json& m_json;
  };

  void err(const std::string& value) {
    std::cout << "configuration error: " << value << std::endl;
  }

} /* namespace */

int main(int ac, char* av[]) {
  try {
    const auto schema = load("./ncdsresources/ControlMessageSchema.avsc");

    kf::config_t tmp;
    std::ifstream ifs("config.json");
    nlohmann::json j = nlohmann::json::parse(ifs);
    std::cout << j << std::endl;
    read_json_t rj(j);
    tmp.read_config(rj, err);

    std::string error;

    auto conf = tmp.get_config();
    conf->set("auto.offset.reset", "earliest", error);
    conf->set("group.id", "Control-ffineu-tyapkin", error);

    std::unique_ptr<RdKafka::KafkaConsumer> consumer(RdKafka::KafkaConsumer::create(tmp.get_config(), error));
    if(!consumer)
      throw(std::runtime_error("can`t create consumer"));


    std::vector<RdKafka::TopicPartition*> partitions;
    std::unique_ptr<RdKafka::TopicPartition> topic_partition(
      RdKafka::TopicPartition::create("control", 0, RdKafka::Topic::OFFSET_BEGINNING));
    partitions.push_back(topic_partition.get());
    RdKafka::ErrorCode assign_error = consumer->assign(partitions);

    std::unique_ptr<RdKafka::Message> msg = std::unique_ptr<RdKafka::Message>(consumer->consume(0));
    pbuffer(msg->payload(), msg->len());


    seek_to_midnight_at_past_day(consumer.get(), topic_partition.get(), 0);


    consumer->subscribe({"control"});
    while(true) {
      auto msg = std::unique_ptr<RdKafka::Message>(consumer->consume(3000));
      std::cout << "size: " << msg->len() << std::endl; 
      pbuffer(msg->payload(), msg->len());
    }




  }
  catch(const std::exception& e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}
