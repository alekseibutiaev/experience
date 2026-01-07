# - Try to find the PUGIXML library 
# Once done this will define
#
#  PUGIXML_FOUND - system has PUGIXML
#  PUGIXML_INCLUDE_DIR - the PUGIXML include directory
#  PUGIXML_LIBRARIES - Link these to use PUGIXML


if(PUGIXML_INCLUDE_DIR AND PUGIXML_LIBRARIES)
  set(PUGIXML_FOUND TRUE)
else(PUGIXML_INCLUDE_DIR AND PUGIXML_LIBRARIES)
  find_path(PUGIXML_INCLUDE_DIR NAMES pugixml.hpp
    HINTS
      ${PUGIXML_HOME}/include
    PATHS
      /usr/include
      /opt/pugixml/include
  )

  if(PUGIXML_STATIC)
    set(PUGIXML_LIB_NAME libpugixml.a)
  else(PUGIXML_STATIC)
    set(PUGIXML_LIB_NAME pugixml)
  endif(PUGIXML_STATIC)

  find_library(PUGIXML_LIBRARY NAMES ${PUGIXML_LIB_NAME}
    HINTS
      ${PUGIXML_HOME}/lib
    PATHS
      /usr/lib
      /usr/lib/x86_64-linux-gnu
      /usr/lib/i386-linux-gnu
  )

  set(PUGIXML_LIBRARIES ${PUGIXML_LIBRARY} CACHE STRING " Libraries needed for PUGIXML")
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(PUGIXML DEFAULT_MSG PUGIXML_INCLUDE_DIR PUGIXML_LIBRARY)
  mark_as_advanced(PUGIXML_INCLUDE_DIR PUGIXML_LIBRARIES)

endif(PUGIXML_INCLUDE_DIR AND PUGIXML_LIBRARIES)
