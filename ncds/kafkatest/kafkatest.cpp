#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <thread>

#include <nlohmann/json.hpp>

#include <avro/Generic.hh>
#include <avro/ValidSchema.hh>
#include <avro/Decoder.hh>
#include <avro/Stream.hh>
#include <avro/Compiler.hh>
#include <avro/Specific.hh>

#include <config.h>
#include <consumer.h>

// https://github.com/confluentinc/librdkafka/issues/2758

namespace {

  void pbuffer(const void* buf, const std::size_t& size) {
    char hex[128] = {0};
    char ch[17] = {0};
    for(std::size_t i = 0; i < size; ++i) {
      sprintf(&hex[(i % 16) * 5], "0x%02X ", reinterpret_cast<const unsigned char*>(buf)[i]);
      sprintf(&ch[(i % 16)], "%c", std::isprint(reinterpret_cast<const unsigned char*>(buf)[i]) ?
        reinterpret_cast<const unsigned char*>(buf)[i] : '.');
      if(0 == (i + 1) % 16)
        std::cout << hex << ch << std::endl;
    }
    if(size % 16)
      std::cout << hex << ch << std::endl;
  }

  void print_records(const std::vector<avro::GenericRecord>& records, std::ostream& os) {
    for (auto &record : records) {
      os << "Message: " << record.schema()->name().simpleName() << ' ';
      for (size_t i = 0; i < record.fieldCount(); i++) {
        avro::GenericDatum datum = record.fieldAt(i);
        os << record.schema()->nameAt(i) << ": ";
        if (datum.type() == avro::AVRO_DOUBLE)
          os << datum.value<double>() << ' ';
        else if (datum.type() == avro::AVRO_LONG)
          os << datum.value<int64_t>() << ' ';
        else if (datum.type() == avro::AVRO_INT)
          os << datum.value<int>() << ' ';
        else if (datum.type() == avro::AVRO_STRING)
          os << datum.value<std::string>() << ' ';
      }
      os << std::endl;
    }
  }

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
    decode_t(const avro::ValidSchema& schema)
      : m_decoder(avro::binaryDecoder())
      , m_schema(schema)
      , m_datum(std::make_shared<avro::GenericDatum>(m_schema)) {
    }

    void operator()(const std::string& topic, const void* buf, const std::size_t size) const {
      std::cout << topic << std::endl;
    }
  private:
    avro::DecoderPtr m_decoder;
    const avro::ValidSchema m_schema;
    std::shared_ptr<avro::GenericDatum> m_datum;    
  };

  class decode_ex_t {
  public:
    decode_ex_t(const std::string ctrl_schema)
      : m_decoder(avro::binaryDecoder())
      , m_control_schema(load(ctrl_schema))
      , m_datum_schema(std::make_shared<avro::GenericDatum>(m_control_schema)) {
    }
    void operator()(const std::string& topic, const void* buf, const std::size_t size) const {
//      std::cout << topic << std::endl;
      if("control" == topic)
        const_cast<decode_ex_t&>(*this).update_control(buf, size);
      else {
        auto it = m_schemas.find(topic.substr(0, topic.find(".stream")));
        if(it != m_schemas.end())
          decode_message(topic, std::make_shared<avro::GenericDatum>(it->second), buf, size);
        else
          std::cout << "has not schema for [" + topic + "] topic"  << std::endl;      }
    }
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
      print_records({record}, std::cout);
    }
    void update_control(const void* buf, const std::size_t size) {
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
    map_schemas_t m_schemas;
  };

} /* namespace */

int main(int ac, char* av[]) {
  try {
    std::cout << "test" << std::endl;
    kf::config_t tmp;
    std::ifstream ifs("config.json");
    nlohmann::json j = nlohmann::json::parse(ifs);
    std::cout << j << std::endl;
    const std::vector<std::string> topics(j["topics"].begin(), j["topics"].end());
    const auto ss = j["control_message_schema"];
    decode_ex_t decoder(ss);
    read_json_t rj(j);
    tmp.read_config(rj, err);
    kf::consumer_t consumer(tmp, rj, err);
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
