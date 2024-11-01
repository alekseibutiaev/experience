#pragma once

#include <string>


namespace kf {

  class error_t {
  public:
    virtual ~error_t() = default;
    virtual void debug(const std::string& msg) const = 0;
    virtual void info(const std::string& msg) const = 0;
    virtual void warning(const std::string& msg) const = 0;
    virtual void error(const std::string& msg) const = 0;
  };

} /* namespace kf */