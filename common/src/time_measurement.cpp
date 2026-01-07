#include "logger.hpp"

#include "time_measurement.hpp"

namespace tools {

  time_measurement_t::time_measurement_t(const std::string& message, const tools::level_t::value_t level)
      : m_message(message)
      , m_level(level)
      , m_start(std::chrono::high_resolution_clock::now()) {
  }

  time_measurement_t::~time_measurement_t() {
    const auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - m_start).count();
    char buf[128];
    sprintf(buf, "%ld.%03ld", tmp / 1000, tmp % 1000);
    lo(m_level, m_message, ' ', buf, " second", endline);
  }

} /* namespace tools */
