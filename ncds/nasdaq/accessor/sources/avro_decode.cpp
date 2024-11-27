
#include <map>
#include <mutex>
#include <array>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <shared_mutex>

#include <avro/Decoder.hh>
#include <avro/Generic.hh>
#include <avro/Compiler.hh>
#include <avro/Specific.hh>
#include <avro/ValidSchema.hh>
#include <avro/GenericDatum.hh>

#include "../location.h"

#include "acc_types.h"
#include "tools.h"

#include "avro_decode.h"

namespace {

  nasdaq::acc::avro_decode_t::delegate_t::fields_t get_fields(const avro::NodePtr node) {
    try {
      nasdaq::acc::avro_decode_t::delegate_t::fields_t res;
      for(std::size_t i = 0; i < node->names(); ++i)
        res.push_back(node->nameAt(i));
      return res;
    }
    catch(...) {
      return nasdaq::acc::avro_decode_t::delegate_t::fields_t();
    }
  }

} /* namespace */

namespace nasdaq {

  namespace acc {

    namespace details {

      class avro_decode_t {
      public:
        avro_decode_t(const nasdaq::acc::avro_decode_t& owner, nasdaq::acc::avro_decode_t::delegate_t& delegate,
          const error_t& err, const std::string& ctrl_schema)
            : m_owner(owner)
            , m_delegate(delegate)
            , m_err(err)
            , m_schema_control(load_schema(ctrl_schema))
            , m_schema_datum(std::make_shared<datum_ptr::element_type>(*m_schema_control)) {
          read_tables(nasdaq::acc::avro_decode_t::control, m_schema_control->root());
        }
        void operator()(const time_point_t& tp, std::string stream, const void* buf,
            const std::size_t size) const {
          try {
            stream = stream.substr(0, stream.find(".stream"));
            if(nasdaq::acc::avro_decode_t::control == stream)
              read_control(buf, size);
            else
              decode_message(tp, stream, get_datum(stream), buf, size);
          }
          catch(const std::exception& e) {
            m_err.error(e.what());
          }
        }
        void get_field(const nasdaq::acc::record_t& record, const std::size_t& idx, user_data_t& data) const {
          using signature_t = void(avro_decode_t::*)(const avro::Type&, const std::string&,
              const avro::GenericDatum&, user_data_t&) const;
          static const std::array<signature_t, avro::AVRO_SYMBOLIC> functions = {
            &avro_decode_t::get_field<std::string>, &avro_decode_t::get_field<unsigned char>,
            &avro_decode_t::get_field<int>, &avro_decode_t::get_field<long>,
            &avro_decode_t::get_field<float>, &avro_decode_t::get_field<double>,
            &avro_decode_t::get_field<bool>, &avro_decode_t::get_field_unsuported,
            &avro_decode_t::get_field_unsuported, &avro_decode_t::get_field_unsuported,
            &avro_decode_t::get_field_unsuported, &avro_decode_t::get_field_unsuported,
            &avro_decode_t::get_field_unsuported, &avro_decode_t::get_field_unsuported
          };
          auto datum = record.first->fieldAt(idx);
          auto type = datum.type();
          (this->*functions[type])(type, record.first->schema()->nameAt(idx), datum, data);
        }
        template<typename type_t>
        void get_field(const avro::Type&, const std::string& name, const avro::GenericDatum& datum,
            user_data_t& data) const {
          m_delegate.data(name, datum.value<type_t>(), data);
        }
        void get_field_unsuported(const avro::Type& type, const std::string&,
            const avro::GenericDatum&, user_data_t&) const {
          m_err.warning("unsuported type: " + avro::toString(type) + __FILE_STR__);
        }
      private:
        using schema_ptr = std::shared_ptr<avro::ValidSchema>;
        using map_schemas_t = std::map<std::string, schema_ptr>;
        using datum_ptr = std::shared_ptr<avro::GenericDatum>;
      private:
        void decode_message(const time_point_t& tp, const std::string& stream, datum_ptr datum,
            const void* buf, const std::size_t size) const {
          try {
            auto record = get_record(datum, buf, size);
            m_delegate.message(m_owner, tp, stream, record.first->schema()->name().simpleName(), record);
          }
          catch(const std::exception& e) {
            m_err.error(e.what() + __FILE_STR__);
          }
        }
        void read_control(const void* buf, const std::size_t size) const {
          try {
            std::pair<const char*, std::string> fields[] = {{"referenceDate", ""}, {"name",""}, {"schema",""}};
            record_t record;
            {
              std::unique_lock _(m_lock_schema_datum);
              record = get_record(m_schema_datum, buf, size);
            }
            for (size_t i = 0; i < record.first->fieldCount(); i++) {
              for(auto& field : fields)
                if(field.second.empty() && field.first == record.first->schema()->nameAt(i))
                  field.second = record.first->fieldAt(i).value<std::string>();  
            }
            update_control(fields[1].second, fields[2].second);
          }
          catch(const std::exception& e) {
            m_err.error(__FILE_STR__ + e.what());
          }
        }
        record_t get_record(const datum_ptr& datum, const void* buf, const std::size_t size) const {
          auto in = avro::memoryInputStream(reinterpret_cast<const uint8_t*>(buf), size);
          avro::DecoderPtr decoder(avro::binaryDecoder());
          decoder->init(*in);
          avro::decode(*decoder, *datum);
          return {std::make_shared<avro::GenericRecord>(datum->value<avro::GenericRecord>()), decoder};
        }
        avro_decode_t::datum_ptr get_datum(const std::string& stream) const {
          for(;;){
            {
              std::shared_lock _(m_lock_schemas);
              auto it = m_schemas.find(stream);
              if(it != m_schemas.end())
                return std::make_shared<avro_decode_t::datum_ptr::element_type>(*it->second);
            }
            const auto& schema = m_delegate.load(stream);
            if(schema.empty())
              throw std::runtime_error(__FILE_STR__ + "has not schema for [" + stream + "] stream");
            update_control(stream, schema, false);
          }
        }
        void update_control(const std::string& stream, const std::string& schema, const bool save = true) const {
          try {
            if(!stream.empty() && !schema.empty()) {
              const auto& sch = add_schema(stream, schema);
              read_tables(stream, sch->root());
              if(save && !m_delegate.save(stream, sch->toJson()))
                m_err.warning(__FILE_STR__ + "can`t open schema for stream: " + stream);
            }
          }
          catch(const std::exception& e) {
            m_err.error(e.what() + __FILE_STR__);
          }
        }
        void read_tables(const std::string& stream, const avro::NodePtr node) const {
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
        schema_ptr add_schema(const std::string& stream, const std::string& schema) const {
          std::istringstream iss(schema);
          std::unique_lock _(m_lock_schemas);
          return m_schemas[stream] = avro_decode_t::load_schema(iss);
        }
      private:
        static schema_ptr load_schema(std::istream& is) {
          schema_ptr schema = std::make_shared<schema_ptr::element_type>();
          avro::compileJsonSchema(is, *schema);
          return schema;
        }
        static schema_ptr load_schema(const std::string& file) {
          std::shared_ptr<std::istream> is(file.empty() ?
            static_cast<std::istream*>(new std::istringstream(control_message_schema)) :
            static_cast<std::istream*>(new std::ifstream(file.c_str())));
          if(static_cast<bool>(*is))
            return load_schema(*is);
          throw(std::runtime_error((file.empty() ? std::string("can`t load schema from loal data") :
            "can`t open file: " + file) + __FILE_STR__));
        }
      private:
        static const std::string control_message_schema;
      private:
        const nasdaq::acc::avro_decode_t& m_owner;
        nasdaq::acc::avro_decode_t::delegate_t& m_delegate;
        const error_t& m_err;
        mutable std::mutex m_lock_schema_control;
        const schema_ptr m_schema_control;
        mutable std::mutex m_lock_schema_datum;
        datum_ptr m_schema_datum;
        mutable std::shared_mutex m_lock_schemas;
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
        , m_impl(std::make_shared<details::avro_decode_t>(*this, delegate, m_err, ctrl_schema)) {
    }

    void avro_decode_t::operator()(const time_point_t& tp, const std::string& stream, const void* buf, const std::size_t size) const {
      (*m_impl)(tp, stream, buf, size);
    }

    void avro_decode_t::get_field(const record_t& record, const std::size_t& idx, user_data_t& data) const {
      m_impl->get_field(record, idx, data);
    }

    std::string avro_decode_t::delegate_t::read(const std::string& file) {
      std::string res;
      std::ifstream ifs(file);
      while(ifs)
        res += [](std::istream& is){std::string tmp; is >> tmp; return tmp;}(ifs);
      return res;
    }

    bool avro_decode_t::delegate_t::write(const std::string& file, const std::string& schema) {
      std::ofstream ofs(file);
      const bool res = static_cast<bool>(ofs);
      if(res)
        ofs << schema;
      return res;
    }

  } /* namespace acc */

} /* namespace nasdaq */
