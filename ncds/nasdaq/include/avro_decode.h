#pragma once

#include <memory>
#include <string>

namespace kf {

  namespace details {

    class avro_decode_t;

  } /* namespace details */

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
      virtual void schema(const std::string& name, const std::string& schema);
    };
  public:
    avro_decode_t(delegate_t& delegate, const std::string& ctrl_schema);
    void operator()(const std::string& topic, const void* buf, const std::size_t size) const;
  public:
    const static std::string control;
  private:
    using avro_decode_ptr = std::shared_ptr<details::avro_decode_t>;
  private:
    avro_decode_ptr m_impl;
  };

} /* namespace kf */
