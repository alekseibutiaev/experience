#pragma once
#include <string>

#include <boost/optional.hpp>

namespace cl {

  struct params_t {
    bool help = false;
    bool no_echo = false;
    std::string host;
    unsigned short port = 0;
    std::string file;
  };

  using params_try_t = boost::optional<params_t>;

  params_try_t get_options(int ac, char* av[]);

} /* namespace cl */
