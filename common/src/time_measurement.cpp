#include "time_measurement.hpp"

namespace tools {

  time_measurement_t::time_measurement_t(const std::string& message)
      : m_message(message)
      , m_start(std::chrono::high_resolution_clock::now()) {
  }

  time_measurement_t::~time_measurement_t() {
    const auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::high_resolution_clock::now() - m_start).count();
    lo(m_message, tmp / 1000, '.', tmp % 1000, " second", endline);
  }

} /* namespace tools */
