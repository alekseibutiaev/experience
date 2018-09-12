#pragma once

#include <chrono>

#include "logger.hpp"


namespace tools {

  class time_measurement {

  public:

    time_measurement()
        : m_start(std::chrono::high_resolution_clock::now()) {
    }

    ~time_measurement() {
      const std::chrono::duration<double> time_span =
        std::chrono::duration_cast<std::chrono::duration<double>>(
          std::chrono::high_resolution_clock::now() - m_start);
      logout("Duration is: ", time_span.count(), " second", endline);
    }

  private:

    const std::chrono::high_resolution_clock::time_point m_start;

  };

} /* namespace tools */
