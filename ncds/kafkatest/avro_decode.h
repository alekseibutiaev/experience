#pragma once

#include <map>
#include <memory>
#include <iosfwd>
#include <string>
#include <vector>
#include <functional>


#include <avro/Decoder.hh>
#include <avro/ValidSchema.hh>
#include <avro/GenericDatum.hh>

namespace kf {

  class avro_decode_t {
  public:
    class delegate_t {
    public:
      virtual ~delegate_t() = default;
      virtual void begin_msg(const std::string& topic, const std::string& msg) = 0;
      virtual void end_msg() = 0;
      virtual void data(const std::string& field, const std::string& data) = 0;
      virtual void data(const std::string& field, const unsigned char& data) = 0;
      virtual void data(const std::string& field, const int& data) = 0;
      virtual void data(const std::string& field, const long& data) = 0;
      virtual void data(const std::string& field, const float& data) = 0;
      virtual void data(const std::string& field, const double& data) = 0;
      virtual void data(const std::string& field, const bool& data) = 0;
    };
  public:
    avro_decode_t(delegate_t& delegate, const std::string& ctrl_schema);
    void operator()(const std::string& topic, const void* buf, const std::size_t size) const;
  public:
    const static std::string control;
  private:
    using key_schema_t = std::string;
    using map_schemas_t = std::map<key_schema_t, avro::ValidSchema>;
  private:
    void decode_message(const std::string& topic, std::shared_ptr<avro::GenericDatum> datum,
        const void* buf, const std::size_t size) const;
    void update_control(const void* buf, const std::size_t size) const;
    void read_fields(const std::string& topic, const std::vector<avro::GenericRecord>& records) const;
  private:
    static avro::ValidSchema load_schema(std::istream& is);
    static avro::ValidSchema load_schema(const std::string& file);
  private:
    delegate_t& m_delegate;
    avro::DecoderPtr m_decoder;
    const avro::ValidSchema m_control_schema;
    std::shared_ptr<avro::GenericDatum> m_datum_schema;
    mutable map_schemas_t m_schemas;
  };

} /* namespace kf */
