# - Try to find the DATE library 
# Once done this will define
#
#  DATE_FOUND - system has DATE
#  DATE_INCLUDE_DIR - the DATE include directory
#  DATE_LIBRARIES - Link these to use DATE

if(DATE_INCLUDE_DIR AND DATE_LIBRARIES)
  set(DATE_FOUND TRUE)
else(DATE_INCLUDE_DIR AND DATE_LIBRARIES)
  find_path(DATE_INCLUDE_DIR NAMES date/date.h
    PATHS
      $ENV{DATE_HOME}
      /usr/include
      /opt/date/include
    PATH_SUFFIXES
      /date
  )
  find_library(DATE_LIBRARY NAMES libtz.a
    PATHS
      $ENV{DATE_HOME}
      lib
      /usr/lib
      /usr/lib/x86_64-linux-gnu
      /usr/lib/i386-linux-gnu
      /opt/date/lib
  )
  set(DATE_LIBRARIES ${DATE_LIBRARY} CACHE STRING " Libraries needed for date")
  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(DATE DEFAULT_MSG DATE_INCLUDE_DIR DATE_LIBRARY)
  mark_as_advanced(DATE_INCLUDE_DIR DATE_LIBRARIES)
endif(DATE_INCLUDE_DIR AND DATE_LIBRARIES)
