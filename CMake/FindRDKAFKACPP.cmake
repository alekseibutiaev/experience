# - Try to find the RDKAFKACPP library 
# Once done this will define
#
#  RDKAFKACPP_FOUND - system has RDKAFKACPP
#  RDKAFKACPP_INCLUDE_DIR - the RDKAFKACPP include directory
#  RDKAFKACPP_LIBRARIES - Link these to use RDKAFKACPP


if(RDKAFKACPP_INCLUDE_DIR AND RDKAFKACPP_LIBRARIES)
  set(RDKAFKACPP_FOUND TRUE)
else(RDKAFKACPP_INCLUDE_DIR AND RDKAFKACPP_LIBRARIES)
  find_path(RDKAFKACPP_INCLUDE_DIR NAMES librdkafka/rdkafka.h
    HINTS
      ${RDKAFKA_HOME}/include
    PATHS
      /usr/include
  )

  if(RDKAFKACPP_STATIC)
    set(RDKAFKACPP_LIB_NAME librdkafka++.a)
  else(RDKAFKACPP_STATIC)
    set(RDKAFKACPP_LIB_NAME rdkafka++)
  endif(RDKAFKACPP_STATIC)

  find_library(RDKAFKACPP_LIBRARY NAMES ${RDKAFKACPP_LIB_NAME}
    HINTS
      ${RDKAFKA_HOME}/lib
    PATHS
      lib
      /usr/lib
      /usr/lib/x86_64-linux-gnu
      /usr/lib/i386-linux-gnu
  )

  set(RDKAFKACPP_LIBRARIES ${RDKAFKACPP_LIBRARY} CACHE STRING " Libraries needed for RDKAFKACPP")
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(RDKAFKACPP DEFAULT_MSG RDKAFKACPP_INCLUDE_DIR RDKAFKACPP_LIBRARY)
  mark_as_advanced(RDKAFKACPP_INCLUDE_DIR RDKAFKACPP_LIBRARIES)
endif(RDKAFKACPP_INCLUDE_DIR AND RDKAFKACPP_LIBRARIES)
