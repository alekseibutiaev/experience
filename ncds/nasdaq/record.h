#pragma once

#include "types.h"

#include "data_delegate.h"

namespace nasdaq {


  class record_t : public data_delegate_t {
  public:
    virtual ~record_t() = default;
    void data(const std::string& field, const std::string& value) override {

    }
    void data(const std::string& field, const unsigned char& value) override {

    }
    void data(const std::string& field, const int& value) override {

    }
    void data(const std::string& field, const long& value) override {

    }
    void data(const std::string& field, const float& value) override {

    }
    void data(const std::string& field, const double& value) override {

    }
    void data(const std::string& field, const bool& value) override {
      
    }
  };

} /* namespace nasdaq */
