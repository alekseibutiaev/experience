#pragma once

#include <string>

namespace nasdaq {

  class error_t {
  public:
    virtual ~error_t() = default;
    virtual void debug(const std::string& msg) const = 0;
    virtual void info(const std::string& msg) const = 0;
    virtual void warning(const std::string& msg) const = 0;
    virtual void error(const std::string& msg) const = 0;
  };

} /* namespace nasdaq */
