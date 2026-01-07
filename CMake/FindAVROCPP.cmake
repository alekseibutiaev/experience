# - Try to find the AVROCPP library 
# Once done this will define
#
#  AVROCPP_FOUND - system has AVROCPP
#  AVROCPP_INCLUDE_DIR - the AVROCPP include directory
#  AVROCPP_LIBRARIES - Link these to use AVROCPP

if(AVROCPP_INCLUDE_DIR AND AVROCPP_LIBRARIES)
  set(AVROCPP_FOUND TRUE)
else(AVROCPP_INCLUDE_DIR AND AVROCPP_LIBRARIES)
  find_path(AVROCPP_INCLUDE_DIR NAMES avro/Compiler.hh
    HINTS
      ${AVROCPP_HOME}/include
    PATHS
      /usr/include
  )

  if(AVROCPP_STATIC)
    set(AVROCPP_LIB_NAME libavrocpp_s.a)
  else(AVROCPP_STATIC)
    set(AVROCPP_LIB_NAME avrocpp)
  endif(AVROCPP_STATIC)

  find_library(AVROCPP_LIBRARY NAMES ${AVROCPP_LIB_NAME}
    HINTS
      ${AVROCPP_HOME}/lib
    PATHS
      lib
      /usr/lib
      /usr/lib/x86_64-linux-gnu
      /usr/lib/i386-linux-gnu
  )
  set(AVROCPP_LIBRARIES ${AVROCPP_LIBRARY} CACHE STRING " Libraries needed for AVROCPP")
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(AVROCPP DEFAULT_MSG AVROCPP_INCLUDE_DIR AVROCPP_LIBRARY)
  mark_as_advanced(AVROCPP_INCLUDE_DIR AVROCPP_LIBRARIES)
endif(AVROCPP_INCLUDE_DIR AND AVROCPP_LIBRARIES)
