#include <cstdio>

#include "internal/utils/FindResources.h"

std::string get_resource_path() {
  // Default path for (https://cmake.org/cmake/help/v3.0/module/GNUInstallDirs.html) DATADIR
  // If the user sets an environment variable, use that instead
  if(const char* tmp = std::getenv("NCDSRESOURCES"))
      return tmp + std::string("/");
  return "/usr/local/share/ncdsresources/";
}
