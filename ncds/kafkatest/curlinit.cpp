#include "curlinit.h"

namespace kf {

  curl_init_t::curl_init_t() {
    curl_global_init(CURL_GLOBAL_ALL);
  }

  curl_init_t::~curl_init_t() {
    curl_global_cleanup();
  }

} /*namespace kf*/