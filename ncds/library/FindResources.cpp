#include <cstdio>

#include "internal/utils/FindResources.h"

std::string get_resource_path() {
  // Default path for (https://cmake.org/cmake/help/v3.0/module/GNUInstallDirs.html) DATADIR
  // If the user sets an environment variable, use that instead
  static std::string path;
  while(path.empty()) {
    if(const char* tmp = std::getenv("NCDSRESOURCES"))
      path = tmp;
    else
      path = "/usr/local/share/ncdsresources/";
  }
  return path;
}
