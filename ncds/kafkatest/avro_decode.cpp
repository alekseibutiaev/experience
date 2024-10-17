
#include <fstream>
#include <sstream>

#include <avro/Compiler.hh>
#include <avro/Specific.hh>
#include <avro/Generic.hh>


#include "types.h"
#include "tools.h"

#include "avro_decode.h"


namespace kf {

  const std::string avro_decode_t::control = "control"; 

  avro_decode_t::avro_decode_t(avro_decode_t::delegate_t& delegate, const std::string& ctrl_schema)
    : m_delegate(delegate)
    , m_decoder(avro::binaryDecoder())
    , m_control_schema(load_schema(ctrl_schema))
    , m_datum_schema(std::make_shared<avro::GenericDatum>(m_control_schema)) {
  }

  void avro_decode_t::operator()(const std::string& topic, const void* buf, const std::size_t size) const {
    if("control" == topic)
      update_control(buf, size);
    else {
      auto it = m_schemas.find(topic.substr(0, topic.find(".stream")));
      if(it != m_schemas.end())
        decode_message(topic, std::make_shared<avro::GenericDatum>(it->second), buf, size);
      else
        std::cout << "has not schema for [" + topic + "] topic"  << std::endl;      }
  }

  void avro_decode_t::decode_message(const std::string& topic, std::shared_ptr<avro::GenericDatum> datum,
      const void* buf, const std::size_t size) const {
    auto in = avro::memoryInputStream(reinterpret_cast<const uint8_t*>(buf), size);
    m_decoder->init(*in);
    avro::decode(*m_decoder, *datum);
    auto record = datum->value<avro::GenericRecord>();
#if 1
    read_fields(topic, {record});
#else    
    std::cout << topic << ' ';
    tools::print_records({record}, std::cout);
#endif
  }

  void avro_decode_t::update_control(const void* buf, const std::size_t size) const {
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
      m_schemas[name] = load_schema(iss);
      std::cout << "schema for: " << name << " topic" << std::endl;
    }
  }

  void avro_decode_t::read_fields(const std::string& topic, const std::vector<avro::GenericRecord>& records) const {
    for(auto& record : records) {
      m_delegate.begin_msg(topic, record.schema()->name().simpleName());
      for(size_t i = 0; i < record.fieldCount(); i++) {
        avro::GenericDatum datum = record.fieldAt(i);
        if(avro::AVRO_STRING == datum.type())
          m_delegate.data(record.schema()->nameAt(i), datum.value<std::string>());
        else if(avro::AVRO_BYTES == datum.type())
          m_delegate.data(record.schema()->nameAt(i), datum.value<unsigned char>());
        else if(avro::AVRO_INT == datum.type())
          m_delegate.data(record.schema()->nameAt(i), datum.value<int>());
        else if(avro::AVRO_LONG == datum.type())
          m_delegate.data(record.schema()->nameAt(i), datum.value<long>());
        else if(avro::AVRO_FLOAT == datum.type())
          m_delegate.data(record.schema()->nameAt(i), datum.value<float>());
        else if(avro::AVRO_DOUBLE == datum.type())
          m_delegate.data(record.schema()->nameAt(i), datum.value<double>());
        else if(avro::AVRO_BOOL == datum.type())
          m_delegate.data(record.schema()->nameAt(i), datum.value<bool>());
      }
      m_delegate.end_msg();
    }
  }


  avro::ValidSchema avro_decode_t::load_schema(std::istream& is) {
    avro::ValidSchema schema;
    avro::compileJsonSchema(is, schema);
    return schema;
  }

  avro::ValidSchema avro_decode_t::load_schema(const std::string& file) {
    std::ifstream ifs(file.c_str());
    if(!ifs.good())
      throw(std::runtime_error("can`t open file: " + file));
    return load_schema(ifs);
  }

} /* namespace kf */