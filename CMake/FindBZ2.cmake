# - Try to find the BZ2 library 
# Once done this will define
#
#  BZ2_FOUND - system has BZ2
#  BZ2_INCLUDE_DIR - the BZ2 include directory
#  BZ2_LIBRARIES - Link these to use BZ2

if(BZ2_INCLUDE_DIR AND BZ2_LIBRARIES)
  set(BZ2_FOUND TRUE)
else(BZ2_INCLUDE_DIR AND BZ2_LIBRARIES)
  find_path(BZ2_INCLUDE_DIR NAMES bzlib.h
    PATHS
      $ENV{BZ2_HOME}
      /usr/include
  )
  find_library(BZ2_LIBRARY NAMES bz2
    PATHS
      $ENV{BZ2_HOME}
      lib
      /usr/lib
      /usr/lib/x86_64-linux-gnu
      /usr/lib/i386-linux-gnu
  )
  set(BZ2_LIBRARIES ${BZ2_LIBRARY} CACHE STRING " Libraries needed for BZ2")
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(BZ2 DEFAULT_MSG BZ2_INCLUDE_DIR BZ2_LIBRARY)
  mark_as_advanced(BZ2_INCLUDE_DIR BZ2_LIBRARIES)
endif(BZ2_INCLUDE_DIR AND BZ2_LIBRARIES)
