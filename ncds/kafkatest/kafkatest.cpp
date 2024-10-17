#include <iostream>
#include <fstream>
#include <sstream>
#include <function>
#include <stdexcept>
#include <thread>

#include <nlohmann/json.hpp>

#include <avro/Generic.hh>
#include <avro/ValidSchema.hh>
#include <avro/Decoder.hh>
#include <avro/Stream.hh>
#include <avro/Compiler.hh>
#include <avro/Specific.hh>

#include "config.h"
#include "consumer.h"
#include "tools.h"

// https://github.com/confluentinc/librdkafka/issues/2758

namespace {

  avro::ValidSchema load(std::istream& is) {
    avro::ValidSchema schema;
    avro::compileJsonSchema(is, schema);
    return schema;
  }

  avro::ValidSchema load(const std::string& file) {
    std::ifstream ifs(file.c_str());
    if(!ifs.good())
      throw(std::runtime_error("can`t open file: " + file));
    return load(ifs);
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

  class decode_t {
  public:

  public:
    decode_t(const std::string ctrl_schema)
      : m_decoder(avro::binaryDecoder())
      , m_control_schema(load(ctrl_schema))
      , m_datum_schema(std::make_shared<avro::GenericDatum>(m_control_schema)) {
    }
    void operator()(const std::string& topic, const void* buf, const std::size_t size) const {
      if("control" == topic)
        update_control(buf, size);
      else {
        auto it = m_schemas.find(topic.substr(0, topic.find(".stream")));
        if(it != m_schemas.end())
          decode_message(topic, std::make_shared<avro::GenericDatum>(it->second), buf, size);
        else
          std::cout << "has not schema for [" + topic + "] topic"  << std::endl;      }
    }
  public:
    const static std::string control;
  private:
    using key_schema_t = std::string;
    using map_schemas_t = std::map<key_schema_t, avro::ValidSchema>;
  private:
    void decode_message(const std::string& topic, std::shared_ptr<avro::GenericDatum> datum,
        const void* buf, const std::size_t size) const {
      auto in = avro::memoryInputStream(reinterpret_cast<const uint8_t*>(buf), size);
      m_decoder->init(*in);
      avro::decode(*m_decoder, *datum);
      auto record = datum->value<avro::GenericRecord>();
      std::cout << topic << ' ';
      tools::print_records({record}, std::cout);
    }
    void update_control(const void* buf, const std::size_t size) const {
      auto in = avro::memoryInputStream(reinterpret_cast<const uint8_t*>(buf), size);
      m_decoder->init(*in);
      avro::decode(*m_decoder, *m_datum_schema);
      auto record = m_datum_schema->value<avro::GenericRecord>();
      std::string name;
      std::string schema;
      for (size_t i = 0; i < record.fieldCount(); i++) {
        if(name.empty() && "name" == record.schema()->nameAt(i))
          name = record.fieldAt(i).value<std::string>();
        else if(schema.empty() && "schema" == record.schema()->nameAt(i))
          schema = record.fieldAt(i).value<std::string>();
      }
      if(!name.empty() && !schema.empty()) {
        std::istringstream iss(schema);
        m_schemas[name] = load(iss);
        std::cout << "schema for: " << name << " topic" << std::endl;
      }
    }
  private:
    avro::DecoderPtr m_decoder;
    const avro::ValidSchema m_control_schema;
    std::shared_ptr<avro::GenericDatum> m_datum_schema;
    mutable map_schemas_t m_schemas;
  };

  const std::string decode_t::control = "control"; 

} /* namespace */

int main(int ac, char* av[]) {
  try {
    std::cout << "test" << std::endl;
    std::ifstream ifs("config.json");
    nlohmann::json j = nlohmann::json::parse(ifs);
    std::cout << j << std::endl;
    decode_t decoder(j["control_message_schema"]);
    std::vector<std::string> topics = {decode_t::control};
    topics.insert(topics.end(), j["topics"].begin(), j["topics"].end());

    read_json_t rj(j);
    kf::config_t cnf;
    cnf.read_config(rj, err);
    kf::consumer_t consumer(cnf, rj, err);
    consumer.consume(topics, decoder);
    for(;;)
      std::this_thread::sleep_for(std::chrono::seconds(1));
    return 0;
  }
  catch(const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
  return 0;
}
