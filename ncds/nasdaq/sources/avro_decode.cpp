
#include <map>
#include <string>
#include <fstream>
#include <sstream>

#include <avro/Decoder.hh>
#include <avro/ValidSchema.hh>
#include <avro/GenericDatum.hh>
#include <avro/Compiler.hh>
#include <avro/Specific.hh>
#include <avro/Generic.hh>

#include "types.h"
#include "tools.h"

#include "avro_decode.h"

namespace {

  kf::avro_decode_t::delegate_t::fields_t get_fields(const avro::NodePtr& node) {
    try {
      kf::avro_decode_t::delegate_t::fields_t res;
      for(std::size_t i = 0; i < node->names(); ++i)
        res.push_back(node->nameAt(i));
      return res;
    }
    catch(...) {
      return kf::avro_decode_t::delegate_t::fields_t();
    }
  }

} /* namespace */

namespace kf {

  namespace details {

    class avro_decode_t {
    public:
      avro_decode_t(const kf::avro_decode_t& owner, kf::avro_decode_t::delegate_t& delegate, const std::string& ctrl_schema)
          : m_owner(owner)
          , m_delegate(delegate)
          , m_decoder(avro::binaryDecoder())
          , m_schema_control(load_schema(ctrl_schema))
          , m_schema_datum(std::make_shared<avro::GenericDatum>(m_schema_control)) {
        read_tables(kf::avro_decode_t::control, m_schema_control.root());
      }
      void operator()(const std::string& stream, const void* buf, const std::size_t size) const {
        if(kf::avro_decode_t::control == stream)
          update_control(buf, size);
        else {
          const auto _stream = stream.substr(0, stream.find(".stream"));
          auto it = m_schemas.find(_stream);
          if(it != m_schemas.end())
            decode_message(_stream, std::make_shared<avro::GenericDatum>(it->second), buf, size);
          else
            std::cout << "has not schema for [" + _stream + "] stream"  << std::endl;      }

      }
      void get_field(const kf::avro_decode_t::record_ptr& record, const std::size_t& idx) const {
        const auto& name = record->schema()->nameAt(idx);
        auto datum = record->fieldAt(idx);
        const auto type = datum.type();
        if(avro::AVRO_STRING == type)
          m_delegate.data(name, datum.value<std::string>());
        else if(avro::AVRO_BYTES == type)
          m_delegate.data(name, datum.value<unsigned char>());
        else if(avro::AVRO_INT == type)
          m_delegate.data(name, datum.value<int>());
        else if(avro::AVRO_LONG == type)
          m_delegate.data(name, datum.value<long>());
        else if(avro::AVRO_FLOAT == type)
          m_delegate.data(name, datum.value<float>());
        else if(avro::AVRO_DOUBLE == type)
          m_delegate.data(name, datum.value<double>());
        else if(avro::AVRO_BOOL == type)
          m_delegate.data(name, datum.value<bool>());
      }
    private:
      using map_schemas_t = std::map<std::string, avro::ValidSchema>;
    private:
      void decode_message(const std::string& stream, std::shared_ptr<avro::GenericDatum> datum,
          const void* buf, const std::size_t size) const {
        auto in = avro::memoryInputStream(reinterpret_cast<const uint8_t*>(buf), size);
        m_decoder->init(*in);
        avro::decode(*m_decoder, *datum);
        auto record = std::make_shared<avro::GenericRecord>(datum->value<avro::GenericRecord>());
        m_delegate.message(m_owner, stream, record->schema()->name().simpleName(), record);
      }
      void update_control(const void* buf, const std::size_t size) const {
        auto in = avro::memoryInputStream(reinterpret_cast<const uint8_t*>(buf), size);
        m_decoder->init(*in);
        avro::decode(*m_decoder, *m_schema_datum);
        auto record = m_schema_datum->value<avro::GenericRecord>();
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
          read_tables(name, (m_schemas[name] = load_schema(iss)).root());
        }
      }
      void read_tables(const std::string& stream, const avro::NodePtr& node) const {
        try {
          if(avro::AVRO_UNION == node->type())
            for(std::size_t i = 0; i < node->leaves(); ++i)
              read_tables(stream, node->leafAt(i));
          else if(avro::AVRO_RECORD == node->type()) {
            m_delegate.table(stream, node->name().simpleName(), get_fields(node));
          }
        }
        catch(...) {

        }
      }
    private:
      static avro::ValidSchema load_schema(std::istream& is) {
        avro::ValidSchema schema;
        avro::compileJsonSchema(is, schema);
        return schema;
      }
      static avro::ValidSchema load_schema(const std::string& file) {
        if(file.empty()) {
          std::istringstream iss(control_message_schema);
          return load_schema(iss);
        }
        std::ifstream ifs(file.c_str());
        if(!ifs.good())
          throw(std::runtime_error("can`t open file: " + file));
        return load_schema(ifs);
      }
    private:
      static const std::string control_message_schema;
    private:
      const kf::avro_decode_t& m_owner;
      kf::avro_decode_t::delegate_t& m_delegate;
      avro::DecoderPtr m_decoder;
      const avro::ValidSchema m_schema_control;
      std::shared_ptr<avro::GenericDatum> m_schema_datum;
      mutable map_schemas_t m_schemas;
    };

    const std::string avro_decode_t::control_message_schema = "[{\"name\":\"Heartbeat\",\"type\":\"record\",\"namespace\":" \
    "\"com.nasdaq.fq.etl.kafka\",\"fields\":[{\"name\":\"timestamp\",\"type\":\"long\"}]}," \
    "{\"type\":\"record\",\"name\":\"StreamInitiated\",\"namespace\":\"com.nasdaq.fq.etl.kafka\"," \
    "\"fields\":[{\"name\":\"name\",\"type\":\"string\"},{\"name\":\"uuid\",\"type\":\"string\"}," \
    "{\"name\":\"referenceDate\",\"type\":\"string\"},{\"name\":\"soupPartition\",\"type\":\"int\"}," \
    "{\"name\":\"timestamp\",\"type\":\"long\"},{\"name\":\"schema\",\"type\":\"string\"}]}," \
    "{\"type\":\"record\",\"name\":\"StreamCompleted\",\"namespace\":\"com.nasdaq.fq.etl.kafka\"," \
    "\"fields\":[{\"name\":\"uuid\",\"type\":\"string\"},{\"name\":\"timestamp\",\"type\":\"long\"}," \
    "{\"name\":\"finalSequenceNumber\",\"type\":\"long\"}]},{\"type\":\"record\",\"name\":" \
    "\"StreamResumed\",\"namespace\":\"com.nasdaq.fq.etl.kafka\",\"fields\":[{\"name\":\"uuid\"," \
    "\"type\":\"string\"},{\"name\":\"timestamp\",\"type\":\"long\"},{\"name\":\"resumeSequenceNum" \
    "ber\",\"type\":\"long\"}]},{\"type\":\"record\",\"name\":\"StreamDeleted\",\"namespace\":" \
    "\"com.nasdaq.fq.etl.kafka\",\"fields\":[{\"name\":\"uuid\",\"type\":\"string\"}]}]";

  } /* namespace details */

  const std::string avro_decode_t::control = "control"; 

  avro_decode_t::avro_decode_t(avro_decode_t::delegate_t& delegate, const std::string& ctrl_schema)
    : m_impl(std::make_shared<details::avro_decode_t>(*this, delegate, ctrl_schema)) {
  }

  void avro_decode_t::operator()(const std::string& stream, const void* buf, const std::size_t size) const {
    (*m_impl)(stream, buf, size);
  }

  void avro_decode_t::get_field(const avro_decode_t::record_ptr& record, const std::size_t& idx) const {
    m_impl->get_field(record, idx);
  }


  void avro_decode_t::delegate_t::schema(const std::string& name, const std::string& schema) {
  }

} /* namespace kf */