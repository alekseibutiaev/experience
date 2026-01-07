# - Try to find the CGATE library 
# Once done this will define
#
#  CGATE_FOUND - system has CGATE
#  CGATE_INCLUDE_DIR - the CGATE include directory
#  CGATE_LIBRARIES - Link these to use CGATE

IF (CGATE_INCLUDE_DIR AND CGATE_LIBRARIES)
  SET(CGATE_FOUND TRUE)
ELSE (CGATE_INCLUDE_DIR AND CGATE_LIBRARIES)

  find_path(CGATE_INCLUDE_DIR NAMES cgate.h
    PATHS
    /usr/include
    /ust/include/cgate
    /opt/cgate/include
    $ENV{CGATE_HOME}/include
  )

  find_library(CGATE_LIBRARY NAMES cgate
    PATHS
    /usr/lib
    /usr/lib/x86_64-linux-gnu
    /usr/lib/i386-linux-gnu
    /opt/cgate/lib
    $ENV{CGATE_HOME}/lib
  )
if(1)
  find_library(CGATE_JNI_LIBRARY NAMES cgate_jni
    PATHS
    /usr/lib
    /usr/lib/x86_64-linux-gnu
    /usr/lib/i386-linux-gnu
    /opt/cgate/lib
    $ENV{CGATE_HOME}/lib
  )
  find_library(CGATE_P2DB_LIBRARY NAMES P2DB
    PATHS
    /usr/lib
    /usr/lib/x86_64-linux-gnu
    /usr/lib/i386-linux-gnu
    /opt/cgate/lib
    $ENV{CGATE_HOME}/lib
  )
  find_library(CGATE_P2REPLCLIENT_LIBRARY NAMES P2ReplClient
    PATHS
    /usr/lib
    /usr/lib/x86_64-linux-gnu
    /usr/lib/i386-linux-gnu
    /opt/cgate/lib
    $ENV{CGATE_HOME}/lib
  )
  find_library(CGATE_P2SYSEXT_LIBRARY NAMES P2SysExt
    PATHS
    /usr/lib
    /usr/lib/x86_64-linux-gnu
    /usr/lib/i386-linux-gnu
    /opt/cgate/lib
    $ENV{CGATE_HOME}/lib
  )
  find_library(CGATE_P2SYS_LIBRARY NAMES P2Sys
    PATHS
    /usr/lib
    /usr/lib/x86_64-linux-gnu
    /usr/lib/i386-linux-gnu
    /opt/cgate/lib
    $ENV{CGATE_HOME}/lib
  )
  find_library(CGATE_P2TBL_LIBRARY NAMES P2Tbl
    PATHS
    /usr/lib
    /usr/lib/x86_64-linux-gnu
    /usr/lib/i386-linux-gnu
    /opt/cgate/lib
    $ENV{CGATE_HOME}/lib
  )
endif()

  set(CGATE_LIBRARIES ${CGATE_LIBRARY} ${CGATE_JNI_LIBRARY}
    ${CGATE_P2DB_LIBRARY} ${CGATE_P2REPLCLIENT_LIBRARY}
    ${CGATE_P2SYSEXT_LIBRARY} ${CGATE_P2SYS_LIBRARY}
    ${CGATE_P2TBL_LIBRARY} CACHE STRING " Libraries needed for cgate")

  include(FindPackageHandleStandardArgs)

  find_package_handle_standard_args(CGATE DEFAULT_MSG CGATE_INCLUDE_DIR CGATE_LIBRARY)
  #CGATE_LIBRARY
  
  MARK_AS_ADVANCED(CGATE_INCLUDE_DIR CGATE_LIBRARIES)


  ENDIF(CGATE_INCLUDE_DIR AND CGATE_LIBRARIES)
