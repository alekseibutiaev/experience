# - Try to find the FreeTDS library 
# Once done this will define
#
#  FreeTDS_FOUND - system has FreeTDS
#  FreeTDS_INCLUDE_DIR - the FreeTDS include directory
#  FreeTDS_LIBRARIES - Link these to use FreeTDS


IF (FreeTDS_INCLUDE_DIR AND FreeTDS_LIBRARIES )

	# Already in cache
	SET(FREETDS_FOUND TRUE)

ELSE (FreeTDS_INCLUDE_DIR AND FreeTDS_LIBRARIES)

       FIND_PATH(FreeTDS_INCLUDE_DIR NAMES sqldb.h sqlfront.h)

#       FIND_LIBRARY(FreeTDS_TDS_LIBRARIES NAMES tds )

if(SYBDB_STATIC)
  set(SYBDB_LIB_NAME libsybdb.a)
else(SYBDB_STATIC)
  set(SYBDB_LIB_NAME sybdb)
endif(SYBDB_STATIC)

       FIND_LIBRARY(FreeTDS_LIBRARIES NAMES ${SYBDB_LIB_NAME})
  
       #set(FreeTDS_LIBRARIES ${FreeTDS_SYBDB_LIBRARIES} CACHE STRING "Libraries needed for sybase/mssql driver")

       include(FindPackageHandleStandardArgs)
       FIND_PACKAGE_HANDLE_STANDARD_ARGS(FreeTDS DEFAULT_MSG FreeTDS_INCLUDE_DIR FreeTDS_LIBRARIES)

       MARK_AS_ADVANCED(FreeTDS_INCLUDE_DIR FreeTDS_LIBRARIES)

ENDIF (FreeTDS_INCLUDE_DIR AND FreeTDS_LIBRARIES )
