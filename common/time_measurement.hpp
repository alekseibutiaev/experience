#pragma once

#include <chrono>
#include <string>

#include "logger.hpp"


namespace tools {

  class time_measurement_t {
  public:
    time_measurement_t(const std::string& message = std::string("Duration is: "));
    ~time_measurement_t();
  private:
    const std::string m_message;
    const std::chrono::high_resolution_clock::time_point m_start;
  };

} /* namespace tools */
