#include <cstdio>

#include "internal/utils/FindResources.h"

std::string get_resource_path() {
  // Default path for (https://cmake.org/cmake/help/v3.0/module/GNUInstallDirs.html) DATADIR
  std::string path = "/usr/local/share/ncdsresources/";
  // If the user sets an environment variable, use that instead
  if(const char* env_p = std::getenv("NCDSRESOURCES"))
      path = env_p;
  return path;
}
