# - Find V8
# Find the V8 includes and library
#
#  V8_INCLUDE_DIR - Where to find V8 includes
#  V8_LIBRARIES   - List of libraries when using V8
#  V8_FOUND       - True if V8 was found

if(V8_INCLUDE_DIR)
  set(V8_FIND_QUIETLY TRUE)
endif(V8_INCLUDE_DIR)

find_path(V8_INCLUDE_DIR v8/v8.h
  HINTS
    ${V8_HOME}
  PATHS
    /usr
    /usr/local
    /opt/v8lib
  PATH_SUFFIXES
    /include
  DOC "V8 - Headers"
)

find_library(V8_BASE_LIBRARY NAMES v8_base
  HINTS
    ${V8_HOME}
    ${V8_HOME}/lib/x86_64-linux-gnu
    ${V8_HOME}/lib/i386-linux-gnu
  PATHS
    /usr
    /usr/lib
    /usr/lib/x86_64-linux-gnu
    /usr/lib/i386-linux-gnu
    /opt/v8lib/lib/x86_64-linux-gnu
    /opt/v8lib/lib/i386-linux-gnu
  PATH_SUFFIXES
    /v8 
  DOC "V8 - Library"
)

find_library(V8_SNAPSHOT_LIBRARY NAMES v8_snapshot
  HINTS
    ${V8_HOME}
    ${V8_HOME}/lib/x86_64-linux-gnu
    ${V8_HOME}/lib/i386-linux-gnu
  PATHS
    /usr
    /usr/lib
    /usr/lib/x86_64-linux-gnu
    /usr/lib/i386-linux-gnu
    /opt/v8lib/lib/x86_64-linux-gnu
    /opt/v8lib/lib/i386-linux-gnu
  PATH_SUFFIXES
    /v8 
  DOC "V8 - Library"
)

find_library(V8_LIBPLATFORM_LIBRARY NAMES v8_libplatform
  HINTS
    ${V8_HOME}
    ${V8_HOME}/lib/x86_64-linux-gnu
    ${V8_HOME}/lib/i386-linux-gnu
  PATHS
    /usr
    /usr/lib
    /usr/lib/x86_64-linux-gnu
    /usr/lib/i386-linux-gnu
    /opt/v8lib/lib/x86_64-linux-gnu
    /opt/v8lib/lib/i386-linux-gnu
  PATH_SUFFIXES
    /v8
  DOC "V8 - Library platform"
)

find_library(V8_LIBSAMPLER_LIBRARY NAMES v8_libsampler
  HINTS
    ${V8_HOME}
    ${V8_HOME}/lib/x86_64-linux-gnu
    ${V8_HOME}/lib/i386-linux-gnu
  PATHS
    /usr
    /usr/lib
    /usr/lib/x86_64-linux-gnu
    /usr/lib/i386-linux-gnu
    /opt/v8lib/lib/x86_64-linux-gnu
    /opt/v8lib/lib/i386-linux-gnu
  PATH_SUFFIXES
    /v8 
  DOC "V8 - Library"
)

find_library(V8_LIBBASE_LIBRARY NAMES v8_libbase
  HINTS
    ${V8_HOME}
    ${V8_HOME}/lib/x86_64-linux-gnu
    ${V8_HOME}/lib/i386-linux-gnu
  PATHS
    /usr
    /usr/lib
    /usr/lib/x86_64-linux-gnu
    /usr/lib/i386-linux-gnu
    /opt/v8lib/lib/x86_64-linux-gnu
    /opt/v8lib/lib/i386-linux-gnu
  PATH_SUFFIXES
    /v8 
  DOC "V8 - Library"
)

if(V8ICU)
  find_library(V8_ICUI18N_LIBRARY NAMES libv8_icui18n.a
    HINTS
      ${V8_HOME}
      ${V8_HOME}/lib/x86_64-linux-gnu
      ${V8_HOME}/lib/i386-linux-gnu
    PATHS
      /usr
      /usr/lib
      /usr/lib/x86_64-linux-gnu
      /usr/lib/i386-linux-gnu
      /opt/v8lib/lib/x86_64-linux-gnu
      /opt/v8lib/lib/i386-linux-gnu
    PATH_SUFFIXES
      /v8 
    DOC "V8 - Library"
  )
  find_library(V8_ICUUC_LIBRARY NAMES libv8_icuuc.a
    HINTS
      ${V8_HOME}
      ${V8_HOME}/lib/x86_64-linux-gnu
      ${V8_HOME}/lib/i386-linux-gnu
    PATHS
      /usr
      /usr/lib
      /usr/lib/x86_64-linux-gnu
      /usr/lib/i386-linux-gnu
      /opt/v8lib/lib/x86_64-linux-gnu
      /opt/v8lib/lib/i386-linux-gnu
    PATH_SUFFIXES
      /v8 
    DOC "V8 - Library"
  )
else(V8ICU)

  set(V8_ICUI18N_LIBRARY "")
  set(V8_ICUUC_LIBRARY "")

endif(V8ICU)

include(FindPackageHandleStandardArgs)

set(V8_LIBRARIES
  ${V8_BASE_LIBRARY}
  ${V8_SNAPSHOT_LIBRARY}
  ${V8_LIBPLATFORM_LIBRARY}
  ${V8_LIBSAMPLER_LIBRARY}
  ${V8_LIBBASE_LIBRARY}
  ${V8_ICUI18N_LIBRARY}
  ${V8_ICUUC_LIBRARY}
)

find_package_handle_standard_args(V8 DEFAULT_MSG V8_LIBRARIES V8_INCLUDE_DIR)
mark_as_advanced(V8_LIBRARY V8_INCLUDE_DIR)
if(V8_FOUND)
  set(V8_INCLUDE_DIRS ${V8_INCLUDE_DIR})
endif(V8_FOUND)
