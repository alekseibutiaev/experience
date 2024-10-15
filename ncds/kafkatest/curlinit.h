#pragma once

#include <memory>
#include <curl/curl.h>

namespace kf {

  class curl_init_t {
    public:
    curl_init_t();
    ~curl_init_t();
  };

  using curl_init_ptr = std::shared_ptr<curl_init_t>;

} /* namespace kf */
