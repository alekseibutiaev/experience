# - Try to find the ASTSBRIDGE library 
# Once done this will define
#
#  ASTSBRIDGE_FOUND - system has ASTSBRIDGE
#  ASTSBRIDGE_INCLUDE_DIR - the ASTSBRIDGE include directory
#  ASTSBRIDGE_LIBRARIES - Link these to use ASTSBRIDGE

if(ASTSBRIDGE_INCLUDE_DIR AND ASTSBRIDGE_LIBRARIES)
  set(ASTSBRIDGE_FOUND TRUE)
else(ASTSBRIDGE_INCLUDE_DIR AND ASTSBRIDGE_LIBRARIES)
  find_path(ASTSBRIDGE_INCLUDE_DIR NAMES mtesrl.h
    HINTS
      ${ASTSBRIDGE_HOME}/include
    PATHS
      /usr/include
      /opt/mtesrl/include
  )

  if(ASTSBRIDGE_STATIC)
    set(ASTSBRIDGE_LIB_NAME mtesrl)
  else(ASTSBRIDGE_STATIC)
    set(ASTSBRIDGE_LIB_NAME mtesrl)
  endif(ASTSBRIDGE_STATIC)

  find_library(ASTSBRIDGE_LIBRARY NAMES ${ASTSBRIDGE_LIB_NAME}
    HINTS
      ${ASTSBRIDGE_HOME}/lib
    PATHS
      lib
      /usr/lib
      /usr/lib/x86_64-linux-gnu
      /usr/lib/i386-linux-gnu
      /opt/mtesrl/lib
  )
  set(ASTSBRIDGE_LIBRARIES ${ASTSBRIDGE_LIBRARY} CACHE STRING " Libraries needed for ASTSBRIDGE")
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(ASTSBRIDGE DEFAULT_MSG ASTSBRIDGE_INCLUDE_DIR ASTSBRIDGE_LIBRARY)
  mark_as_advanced(ASTSBRIDGE_INCLUDE_DIR ASTSBRIDGE_LIBRARIES)

endif(ASTSBRIDGE_INCLUDE_DIR AND ASTSBRIDGE_LIBRARIES)
