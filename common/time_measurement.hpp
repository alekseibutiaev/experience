#pragma once

#include <chrono>
#include <string>

#include "logger.hpp"

namespace tools {

  class time_measurement_t {
  public:
    time_measurement_t(const std::string& message = std::string("Duration is: "),
      const tools::level_t::value_t level = tools::level_t::e_debug);
    ~time_measurement_t();
  private:
    const std::string m_message;
    const tools::level_t::value_t m_level;
    const std::chrono::high_resolution_clock::time_point m_start;
  };

} /* namespace tools */
