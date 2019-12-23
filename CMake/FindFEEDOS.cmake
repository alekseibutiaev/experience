# - Try to find the FEEDOS library 
# Once done this will define
#
#  FEEDOS_FOUND - system has FEEDOS
#  FEEDOS_INCLUDE_DIR - the FEEDOS include directory
#  FEEDOS_LIBRARIES - Link these to use FEEDOS

if(FEEDOS_INCLUDE_DIR AND FEEDOS_LIBRARIES)
  set(FEEDOS_FOUND TRUE)
else(FEEDOS_INCLUDE_DIR AND FEEDOS_LIBRARIES)
  find_path(FEEDOS_INCLUDE_DIR NAMES feedos/api/api_version.h
    PATHS
    /usr/include
    /ust/include/feedos
    /opt/feedos/api/include
    $ENV{FEEDOS_HOME}/api/include
  )
  find_library(FEEDOS_LIBRARY NAMES feedosapi
    PATHS
    /usr/lib
    /usr/lib/x86_64-linux-gnu
    /usr/lib/i386-linux-gnu
    /opt/feedos/api/lib
    $ENV{FEEDOS_HOME}api/lib
  )
  set(FEEDOS_LIBRARIES ${FEEDOS_LIBRARY} CACHE STRING " Libraries needed for feedos")
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(FEEDOS DEFAULT_MSG FEEDOS_INCLUDE_DIR FEEDOS_LIBRARY)
  mark_as_advanced(FEEDOS_INCLUDE_DIR FEEDOS_LIBRARIES)
endif(FEEDOS_INCLUDE_DIR AND FEEDOS_LIBRARIES)
