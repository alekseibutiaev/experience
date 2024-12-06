#pragma once

#include "types.h"

namespace nasdaq {

  struct long_wrp_t {
    explicit long_wrp_t(const long& value);
    explicit operator long() const;
    long m_value;
  };


  class data_delegate_t {
  public:
    virtual ~data_delegate_t() = default;
    virtual void data(const std::size_t& idx, const std::string& field, const std::string& value) = 0;
    virtual void data(const std::size_t& idx, const std::string& field, const unsigned char& value) = 0;
    virtual void data(const std::size_t& idx, const std::string& field, const int& value) = 0;
    virtual void data(const std::size_t& idx, const std::string& field, const long_wrp_t& value) = 0;
    virtual void data(const std::size_t& idx, const std::string& field, const float& value) = 0;
    virtual void data(const std::size_t& idx, const std::string& field, const double& value) = 0;
    virtual void data(const std::size_t& idx, const std::string& field, const bool& value) = 0;
    virtual void data(const std::size_t& idx, const std::string& field, const time_point_t& value) = 0;
    void data(const std::size_t& idx, const std::string& field, const long& value);
  };

} /* namespace nasdaq */