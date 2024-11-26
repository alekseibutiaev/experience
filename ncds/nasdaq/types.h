#pragma once

#include <string>
#include <chrono>
#include <optional>

namespace nasdaq {

  class user_data_t {
  public:
    virtual ~user_data_t() = default;
  };

  using clock_t = std::chrono::high_resolution_clock;
  using time_point_t = clock_t::time_point;
  using string_try_t = std::optional<std::string>;

} /* namespace nasdaq */
