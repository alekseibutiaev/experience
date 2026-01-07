# - Try to find the XERCESC library 
# Once done this will define
#
#  XERCESC_FOUND - system has XERCESC
#  XERCESC_INCLUDE_DIR - the XERCESC include directory
#  XERCESC_LIBRARIES - Link these to use XERCESC

if(XERCESC_INCLUDE_DIR AND XERCESC_LIBRARIES)
  set(XERCESC_FOUND TRUE)
else(XERCESC_INCLUDE_DIR AND XERCESC_LIBRARIES)
  find_path(XERCESC_INCLUDE_DIR NAMES dom/DOM.hpp
    HINTS
      ${XERCESC_HOME}
    PATHS
      $ENV{XERCES_C_HOME}
      /usr/include
      /opt/xerces-c/include
    PATH_SUFFIXES
      /xercesc
  )
  if(XERCESC_STATIC)
    set(XERCESC_LIB_NAME libxerces-c.a)
  else(XERCESC_STATIC)
    set(XERCESC_LIB_NAME xerces-c)
  endif(XERCESC_STATIC)

  find_library(XERCESC_LIBRARY NAMES ${XERCESC_LIB_NAME}
    HINTS
      ${XERCESC_HOME}
    PATHS
      lib
      /usr/lib
      /usr/lib/x86_64-linux-gnu
      /usr/lib/i386-linux-gnu
      /opt/xerces-c/lib
  )


  set(XERCESC_LIBRARIES ${XERCESC_LIBRARY} CACHE STRING " Libraries needed for date")
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(XERCESC DEFAULT_MSG XERCESC_INCLUDE_DIR XERCESC_LIBRARY)
  mark_as_advanced(XERCESC_INCLUDE_DIR XERCESC_LIBRARIES)
endif(XERCESC_INCLUDE_DIR AND XERCESC_LIBRARIES)
