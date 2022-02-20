#include <iostream>
#include <boost/program_options.hpp>

#include "clparametrs.h"

namespace cl {

  params_try_t get_options(int ac, char* av[]) {
    params_t res;
    boost::program_options::options_description opt("tsexec options");
    opt.add_options()
      ("help,h", boost::program_options::bool_switch(&res.help)->default_value(res.help),
          "show help")
      ("no_echo,n", boost::program_options::bool_switch(&res.no_echo)->default_value(res.no_echo),
          "if set then server do not send echo")
      ("host,H", boost::program_options::value(&res.host)->default_value(res.host),
          "host")
      ("file,F", boost::program_options::value(&res.file)->default_value(res.file),
          "file name for local socket")
      ("port,p", boost::program_options::value(&res.port)->default_value(res.port),
          "ip port. can not by 0");
    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(ac, av, opt), vm);
    boost::program_options::notify(vm);
    if(res.help || (res.file.empty() && 0 == res.port)) {
      std::cout << opt << std::endl;
      return params_try_t();
    }
    return params_try_t(res);
  }

} /* namespace cl */
