# - Try to find the QUICKFIX library 
# Once done this will define
#
#  QUICKFIX_FOUND - system has QUICKFIX
#  QUICKFIX_INCLUDE_DIR - the QUICKFIX include directory
#  QUICKFIX_LIBRARIES - Link these to use QUICKFIX

if(QUICKFIX_INCLUDE_DIR AND QUICKFIX_LIBRARIES)
  set(QUICKFIX_FOUND TRUE)
else(QUICKFIX_INCLUDE_DIR AND QUICKFIX_LIBRARIES)
  find_path(QUICKFIX_INCLUDE_DIR NAMES quickfix/config-all.h
    HINTS
      ${QUICKFIX_HOME}/include
    PATHS
      /usr/include
      /opt/quickfix/include
  )

  if(QUICKFIX_STATIC)
    set(QUICKFIX_LIB_NAME libquickfix.a)
  else(QUICKFIX_STATIC)
    set(QUICKFIX_LIB_NAME quickfix)
  endif(QUICKFIX_STATIC)

  find_library(QUICKFIX_LIBRARY NAMES ${QUICKFIX_LIB_NAME}
    HINTS
      ${QUICKFIX_HOME}/lib
    PATHS
      lib
      /usr/lib
      /usr/lib/x86_64-linux-gnu
      /usr/lib/i386-linux-gnu
      /opt/quickfix/lib
  )
  set(QUICKFIX_LIBRARIES ${QUICKFIX_LIBRARY} CACHE STRING " Libraries needed for QUICKFIX")
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(QUICKFIX DEFAULT_MSG QUICKFIX_INCLUDE_DIR QUICKFIX_LIBRARY)
  mark_as_advanced(QUICKFIX_INCLUDE_DIR QUICKFIX_LIBRARIES)
endif(QUICKFIX_INCLUDE_DIR AND QUICKFIX_LIBRARIES)
