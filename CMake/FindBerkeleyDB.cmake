# - Try to find the BERKLAYDB library 
# Once done this will define
#
#  BERKLAYDB_FOUND - system has BERKLAYDB
#  BERKLAYDB_INCLUDE_DIR - the BERKLAYDB include directory
#  BERKLAYDB_LIBRARIES - Link these to use BERKLAYDB

if(BERKLAYDB_INCLUDE_DIR AND BERKLAYDB_LIBRARIES)
  set(BERKLAYDB_FOUND TRUE)
else(BERKLAYDB_INCLUDE_DIR AND BERKLAYDB_LIBRARIES)

  if(BERKLAYDB_CXX)
    set(BERKLAYDB_CXX_INCLUDES_NAME "db_cxx.h")
  else (BERKLAYDB_CXX)
    set(BERKLAYDB_CXX_INCLUDES_NAME "")
  endif(BERKLAYDB_CXX)

  if(BERKLAYDB_STL)
    set(BERKLAYDB_STL_INCLUDES_NAME " dbstl_base_iterator.h dbstl_common.h dbstl_container.h dbstl_dbc.h dbstl_dbt.h dbstl_element_ref.h
      dbstl_exception.h dbstl_inner_utility.h dbstl_map.h dbstl_resource_manager.h dbstl_set.h dbstl_utility.h
      dbstl_vector.h"
    )
  else(BERKLAYDB_STL)
    set(BERKLAYDB_STL_INCLUDES_NAME "")
  endif(BERKLAYDB_STL)

  find_path(BERKLAYDB_INCLUDE_DIR NAMES db.h db_185.h
    HINTS
      ${BERKLAYDB_HOME}/include
    PATHS
      /usr/include
      /opt/db/include
  )

  if(BERKLAYDB_STATIC)
    set(BERKLAYDB_DB_LIB_NAME libdb.a)
  else(BERKLAYDB_STATIC)
    set(BERKLAYDB_DB_LIB_NAME db)
  endif(BERKLAYDB_STATIC)

  find_library(BERKLAYDB_DB_LIBRARY NAMES ${BERKLAYDB_DB_LIB_NAME}
    HINTS
      ${BERKLAYDB_HOME}/lib
    PATHS
      lib
      /usr/lib
      /usr/lib/x86_64-linux-gnu
      /usr/lib/i386-linux-gnu
      /opt/db/lib
  )

  if(BERKLAYDB_CXX)
    if(BERKLAYDB_STATIC)
      set(BERKLAYDB_CXX_LIB_NAME libdb_cxx.a)
    else(BERKLAYDB_STATIC)
      set(BERKLAYDB_CXX_LIB_NAME db_cxx)
    endif(BERKLAYDB_STATIC)

    find_library(BERKLAYDB_CXX_LIBRARY NAMES ${BERKLAYDB_CXX_LIB_NAME}
    HINTS
      ${BERKLAYDB_HOME}/lib
    PATHS
      lib
      /usr/lib
      /usr/lib/x86_64-linux-gnu
      /usr/lib/i386-linux-gnu
      /opt/db/lib
    )
  endif(BERKLAYDB_CXX)

  if(BERKLAYDB_STL)
    if(BERKLAYDB_STATIC)
      set(BERKLAYDB_STL_LIB_NAME libdb_stl.a)
    else(BERKLAYDB_STATIC)
      set(BERKLAYDB_STL_LIB_NAME db_stl)
    endif(BERKLAYDB_STATIC)

    find_library(BERKLAYDB_STL_LIBRARY NAMES ${BERKLAYDB_STL_LIB_NAME}
    HINTS
      ${BERKLAYDB_HOME}/lib
    PATHS
      lib
      /usr/lib
      /usr/lib/x86_64-linux-gnu
      /usr/lib/i386-linux-gnu
      /opt/db/lib
    )
  endif(BERKLAYDB_STL)

  include(FindPackageHandleStandardArgs)

  set(BERKLAYDB_LIBRARIES
    ${BERKLAYDB_DB_LIBRARY}
    ${BERKLAYDB_CXX_LIBRARY}
    ${BERKLAYDB_STL_LIBRARY}
  )

#  set(BERKLAYDB_LIBRARIES ${BERKLAYDB_LIBRARY} CACHE STRING " Libraries needed for BERKLAYDB")

  find_package_handle_standard_args(BERKLAYDB DEFAULT_MSG BERKLAYDB_INCLUDE_DIR BERKLAYDB_LIBRARIES)
  mark_as_advanced(BERKLAYDB_INCLUDE_DIR BERKLAYDB_LIBRARY)
endif(BERKLAYDB_INCLUDE_DIR AND BERKLAYDB_LIBRARIES)
