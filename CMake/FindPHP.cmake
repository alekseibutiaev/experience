# - Try to find the PHP library 
# Once done this will define
#
#  PHP_FOUND - system has PHP
#  PHP_INCLUDE_DIR - the PHP include directory
#  PHP_LIBRARIES - Link these to use PHP

if(PHP_INCLUDE_DIR AND PHP_LIBRARIES)
  set(PHP_FOUND TRUE)
else(PHP_INCLUDE_DIR AND PHP_LIBRARIES)
  find_path(PHP_INCLUDE_DIR NAMES php/main/php.h
    HINTS
      ${PHP_HOME}/include
    PATHS
      /usr/include
      /opt/php/include
  )
  find_library(PHP_LIBRARY NAMES opcache.so
    HINTS
      ${PHP_HOME}/lib/php/extensions/no-debug-non-zts
    PATHS
      lib
      /opt/php/lib/php/extensions/no-debug-non-zts
  )
  set(PHP_LIBRARIES ${PHP_LIBRARY} CACHE STRING " Libraries needed for PHP")
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(PHP DEFAULT_MSG PHP_INCLUDE_DIR PHP_LIBRARY)
  mark_as_advanced(PHP_INCLUDE_DIR PHP_LIBRARIES)
endif(PHP_INCLUDE_DIR AND PHP_LIBRARIES)
