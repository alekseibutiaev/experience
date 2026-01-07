#pragma once

#include <iosfwd>
#include <memory>
#include <functional>

namespace tools {

  using function_t = std::function<void()>;
  using executor_t = std::function<void(function_t)>;

  using ostream_ptr = std::shared_ptr<std::ostream>;

};