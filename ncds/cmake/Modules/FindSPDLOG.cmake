# - Try to find the SPDLOG library 
# Once done this will define
#
#  SPDLOG_FOUND - system has SPDLOG
#  SPDLOG_INCLUDE_DIR - the SPDLOG include directory
#  SPDLOG_LIBRARIES - Link these to use SPDLOG


if(SPDLOG_INCLUDE_DIR AND SPDLOG_LIBRARIES)
  set(SPDLOG_FOUND TRUE)
else(SPDLOG_INCLUDE_DIR AND SPDLOG_LIBRARIES)
  find_path(SPDLOG_INCLUDE_DIR NAMES spdlog/spdlog.h spdlog.h
    HINTS
      ${SPDLOG_HOME}/include
    PATHS
      /usr/include
  )

  set(SPDLOG_LIB_NAME libspdlog.a)
  
  find_library(SPDLOG_LIBRARY NAMES ${SPDLOG_LIB_NAME}
    HINTS
      ${SPDLOG_HOME}/lib
    PATHS
      lib
      /usr/lib
      /usr/lib/x86_64-linux-gnu
      /usr/lib/i386-linux-gnu
  )
  set(SPDLOG_LIBRARIES ${SPDLOG_LIBRARY} CACHE STRING " Libraries needed for SPDLOG")
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(SPDLOG DEFAULT_MSG SPDLOG_INCLUDE_DIR SPDLOG_LIBRARY)
  mark_as_advanced(SPDLOG_INCLUDE_DIR SPDLOG_LIBRARIES)
endif(SPDLOG_INCLUDE_DIR AND SPDLOG_LIBRARIES)
