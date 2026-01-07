# - Try to find the QUICKFAST library 
# Once done this will define
#
#  QUICKFAST_FOUND - system has QUICKFAST
#  QUICKFAST_INCLUDE_DIR - the QUICKFAST include directory
#  QUICKFAST_LIBRARIES - Link these to use QUICKFAST

if(QUICKFAST_INCLUDE_DIR AND QUICKFAST_LIBRARIES)
  set(QUICKFAST_FOUND TRUE)
else(QUICKFAST_INCLUDE_DIR AND QUICKFAST_LIBRARIES)
  find_path(QUICKFAST_INCLUDE_DIR NAMES QuickFAST/Application/QuickFAST.h
    HINTS
      ${QUICKFAST_HOME}
    PATHS
      /usr/include
      /opt/quickfast/include
  )

  if(QUICKFAST_STATIC)
    set(QUICKFAST_LIB_NAME libQuickFAST.a)
  else(QUICKFAST_STATIC)
    set(QUICKFAST_LIB_NAME QuickFAST)
  endif(QUICKFAST_STATIC)

  find_library(QUICKFAST_LIBRARY NAMES ${QUICKFAST_LIB_NAME}
    HINTS
      ${QUICKFAST_HOME}
    PATHS
      lib
      /usr/lib
      /usr/lib/x86_64-linux-gnu
      /usr/lib/i386-linux-gnu
      /opt/quickfast/lib
  )
  set(QUICKFAST_LIBRARIES ${QUICKFAST_LIBRARY} CACHE STRING " Libraries needed for QuickFAST")
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(QUICKFAST DEFAULT_MSG QUICKFAST_INCLUDE_DIR QUICKFAST_LIBRARY)
  mark_as_advanced(QUICKFAST_INCLUDE_DIR QUICKFAST_LIBRARIES)
endif(QUICKFAST_INCLUDE_DIR AND QUICKFAST_LIBRARIES)
