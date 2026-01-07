#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <cerrno>
#include <cstring>

#include <fstream>

#include "daemon.hpp"

namespace {

  const int fds[] = { STDIN_FILENO, STDOUT_FILENO, STDERR_FILENO };
  const char* fdsn[] = { "stdin", "stdout", "stderr" };

} /* namespace */

namespace tools {

  int daemon(const char* pid_file) {
    std::ofstream templog("/tmp/tsexec.fork.log");
    const pid_t pid = fork();
    if(pid) {
      if(0 > pid)
        templog << "can`t open a child process. reason:" << std::strerror(errno) << std::endl;
      return pid;
    }
    const pid_t cpid = tools::pid();
    templog << "child process created. pid: " << cpid << std::endl;
    /* Change the file mode mask */
    umask(0);
    const pid_t sid = setsid();
    if(0 > sid) {
      templog << "can`t create new SID for the child process. reason:" <<
        std::strerror(errno) << std::endl;
      return -1;
    }
    templog << "new sid for the child process created. sid: " << sid << std::endl;
    if(0 > chdir("/")) {
      templog << "can`t create new SID for the child process. reason:" <<
        std::strerror(errno) << std::endl;
      return -1;
    }
    templog << "current working directory changed to \"/\"" << std::endl;

    for(auto i : fds) {
      close(STDIN_FILENO);
      int fd = open("/dev/null", 0);
      if(0 > fd) {
        templog << "can`t open file " << fdsn[i] << " reason:" <<
          std::strerror(errno) << std::endl;
        return -1;
      }
      if(0 <= dup2(fd, i))
        continue;
      templog << "can`t dud2 " << fdsn[i] << " reason:" << std::strerror(errno) << std::endl;
      return -1;
    }

    std::ofstream pp(pid_file);
    if(!pp.good())
      templog << "can`t create file: " << pid_file << std::endl;
    else
      pp << cpid;
    templog << "daemon was created successfully. daemon pid is: " << cpid << std::endl;
    return 0;
  }

  int pid() {
    return getpid();
  }

} /* namespace tools */
