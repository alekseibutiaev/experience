#pragma once

#include <memory>
#include <vector>
#include <string>

#include "types.h"
#include "error.h"

namespace nasdaq {

  namespace details {

    class avro_decode_t;

  } /* namespace details */

  class avro_decode_t {
  public:
    class delegate_t {
    public:
      using fields_t = std::vector<std::string>;
    public:
      virtual ~delegate_t() = default;
      virtual void table(const std::string& stream, const std::string& msg, const fields_t& fields) = 0;
      virtual void message(const avro_decode_t& decoder, const time_point_t& tp, const std::string& stream,
          const std::string& msg, const record_t record) = 0;
      virtual bool save(const std::string& stream, const std::string& schema) = 0;
      virtual std::string load(const std::string& stream) = 0;
      virtual void data(const std::string& field, const std::string& data) = 0;
      virtual void data(const std::string& field, const unsigned char& data) = 0;
      virtual void data(const std::string& field, const int& data) = 0;
      virtual void data(const std::string& field, const long& data) = 0;
      virtual void data(const std::string& field, const float& data) = 0;
      virtual void data(const std::string& field, const double& data) = 0;
      virtual void data(const std::string& field, const bool& data) = 0;
    protected:
      std::string read(const std::string& file);
      bool write(const std::string& file, const std::string& schema);
    };
  public:
    avro_decode_t(delegate_t& delegate, const error_t& err, const std::string& ctrl_schema = std::string());
    void operator()(const time_point_t& tp, const std::string& stream, const void* buf, const std::size_t size) const;
    void get_field(const record_t& record, const std::size_t& idx) const;
  public:
    const static std::string control;
  private:
    using avro_decode_ptr = std::shared_ptr<details::avro_decode_t>;
  private:
    const error_t& m_err;
    avro_decode_ptr m_impl;
  };

} /* namespace nasdaq */
