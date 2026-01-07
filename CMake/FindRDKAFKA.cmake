# - Try to find the RDKAFKA library 
# Once done this will define
#
#  RDKAFKA_FOUND - system has RDKAFKA
#  RDKAFKA_INCLUDE_DIR - the RDKAFKA include directory
#  RDKAFKA_LIBRARIES - Link these to use RDKAFKA


if(RDKAFKA_INCLUDE_DIR AND RDKAFKA_LIBRARIES)
  set(RDKAFKA_FOUND TRUE)
else(RDKAFKA_INCLUDE_DIR AND RDKAFKA_LIBRARIES)
  find_path(RDKAFKA_INCLUDE_DIR NAMES librdkafka/rdkafka.h
    HINTS
      ${RDKAFKA_HOME}/include
    PATHS
      /usr/include
  )

  if(RDKAFKA_STATIC)
    set(RDKAFKA_LIB_NAME librdkafka.a)
  else(RDKAFKA_STATIC)
    set(RDKAFKA_LIB_NAME rdkafka)
  endif(RDKAFKA_STATIC)

  find_library(RDKAFKA_LIBRARY NAMES ${RDKAFKA_LIB_NAME}
    HINTS
      ${RDKAFKA_HOME}/lib
    PATHS
      lib
      /usr/lib
      /usr/lib/x86_64-linux-gnu
      /usr/lib/i386-linux-gnu
  )
  set(RDKAFKA_LIBRARIES ${RDKAFKA_LIBRARY} CACHE STRING " Libraries needed for RDKAFKA")
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(RDKAFKA DEFAULT_MSG RDKAFKA_INCLUDE_DIR RDKAFKA_LIBRARY)
  mark_as_advanced(RDKAFKA_INCLUDE_DIR RDKAFKA_LIBRARIES)
endif(RDKAFKA_INCLUDE_DIR AND RDKAFKA_LIBRARIES)
