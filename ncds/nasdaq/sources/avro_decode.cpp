
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include <avro/Decoder.hh>
#include <avro/ValidSchema.hh>
#include <avro/GenericDatum.hh>
#include <avro/Compiler.hh>
#include <avro/Specific.hh>
#include <avro/Generic.hh>

#include "types.h"
#include "tools.h"
#include "location.h"

#include "avro_decode.h"

namespace avro {

  class GenericDatum;
  class ValidSchema;

} /* namespace avro */

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
      avro_decode_t(const kf::avro_decode_t& owner, kf::avro_decode_t::delegate_t& delegate,
        const error_t& err, const std::string& ctrl_schema)
          : m_owner(owner)
          , m_delegate(delegate)
          , m_err(err)
          , m_decoder(avro::binaryDecoder())
          , m_schema_control(load_schema(ctrl_schema))
          , m_schema_datum(std::make_shared<datum_ptr::element_type>(m_schema_control)) {
        read_tables(kf::avro_decode_t::control, m_schema_control.root());
      }
      void operator()(std::string stream, const void* buf, const std::size_t size) const {
        try {
          stream = stream.substr(0, stream.find(".stream"));
          if(kf::avro_decode_t::control == stream)
            read_control(buf, size);
          else
            decode_message(stream, get_datum(stream), buf, size);
        }
        catch(const std::exception& e) {
          m_err.error(e.what());
        }
      }
      void get_field(const kf::record_ptr& record, const std::size_t& idx) const {
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
      using datum_ptr = std::shared_ptr<avro::GenericDatum>;
    private:
      void decode_message(const std::string& stream, datum_ptr datum, const void* buf,
          const std::size_t size) const {
        auto record = get_record(datum, buf, size);
        m_delegate.message(m_owner, stream, record->schema()->name().simpleName(), record);
      }
      void read_control(const void* buf, const std::size_t size) const {
        try {
          std::pair<const char*, std::string> fields[] = {{"referenceDate", ""}, {"name",""}, {"schema",""}};
          auto record = get_record(m_schema_datum, buf, size);
          for (size_t i = 0; i < record->fieldCount(); i++) {
            for(auto& field : fields)
              if(field.second.empty() && field.first == record->schema()->nameAt(i))
                field.second = record->fieldAt(i).value<std::string>();  
          }
          update_control(fields[1].second, fields[2].second);
        }
        catch(const std::exception& e) {
          m_err.error(__FILE_STR__ + e.what());
        }
      }

      const record_ptr get_record(const datum_ptr& datum, const void* buf, const std::size_t size) const {
        auto in = avro::memoryInputStream(reinterpret_cast<const uint8_t*>(buf), size);
        m_decoder->init(*in);
        avro::decode(*m_decoder, *datum);
        return std::make_shared<record_ptr::element_type>(datum->value<record_ptr::element_type>());
      }

      avro_decode_t::datum_ptr get_datum(const std::string& stream) const {
        for(;;){
          auto it = m_schemas.find(stream);
          if(it != m_schemas.end())
            return std::make_shared<avro_decode_t::datum_ptr::element_type>(it->second);
          else {
            const auto schema = m_delegate.load(stream);
            if(schema.empty())
              throw std::runtime_error(__FILE_STR__ + "has not schema for [" + stream + "] stream");
            update_control(stream, schema, false);
          }
        }
      }
      void update_control(const std::string& stream,const std::string& schema, const bool save = true) const {
        try {
          if(!stream.empty() && !schema.empty()) {
            std::istringstream iss(schema);
            read_tables(stream, (m_schemas[stream] = load_schema(iss)).root());
            if(save && !m_delegate.save(stream, m_schemas[stream].toJson()))
              m_err.warning(__FILE_STR__ + "can`t open schema for stream: " + stream);
          }
        }
        catch(const std::exception& e) {
          m_err.error(  e.what());
        }
      }
      void read_tables(const std::string& stream, const avro::NodePtr& node) const {
        try {
          if(avro::AVRO_UNION == node->type())
            for(std::size_t i = 0; i < node->leaves(); ++i)
              read_tables(stream, node->leafAt(i));
          else if(avro::AVRO_RECORD == node->type())
            m_delegate.table(stream, node->name().simpleName(), get_fields(node));
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
      const error_t& m_err;
      avro::DecoderPtr m_decoder;
      const avro::ValidSchema m_schema_control;
      datum_ptr m_schema_datum;
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

  avro_decode_t::avro_decode_t(delegate_t& delegate, const error_t& err, const std::string& ctrl_schema)
      : m_err(err)
      , m_impl(std::make_shared<details::avro_decode_t>(*this, delegate, err, ctrl_schema)) {
  }

  void avro_decode_t::operator()(const std::string& stream, const void* buf, const std::size_t size) const {
    (*m_impl)(stream, buf, size);
  }

  void avro_decode_t::get_field(const record_ptr& record, const std::size_t& idx) const {
    m_impl->get_field(record, idx);
  }

  std::string avro_decode_t::delegate_t::read(const std::string& file) {
    std::string res;
    std::ifstream ifs(file);
    while(ifs)
      res += [](std::istream& is){ std::string tmp; is >> tmp; return tmp;}(ifs);
    return res;
  }

  bool avro_decode_t::delegate_t::write(const std::string& file, const std::string& schema) {
    std::ofstream ofs(file);
    const bool res = static_cast<bool>(ofs);
    if(res)
      ofs << schema;
    return res;
#if 0
    }
    else
      m_err.warning(__FILE_STR__ + "can`t open file: " + file);
#endif
  }

} /* namespace kf */
