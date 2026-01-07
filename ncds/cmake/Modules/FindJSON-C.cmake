INCLUDE( FindPackageHandleStandardArgs )

# Checks an environment variable; note that the first check
# does not require the usual CMake $-sign.
IF(JSON-C_DIR)
    message("JSON-C_DIR was defined: " ${JSON-C_DIR})
ENDIF()

FIND_PATH(
        JSON-C_INCLUDE_DIR
        json-c/json.h json.h
        HINTS
        ${JSON-C_DIR}/build
)

FIND_LIBRARY( JSON-C_LIBRARY json-c
        HINTS ${JSON-C_DIR}/build
         REQUIRED)


FIND_PACKAGE_HANDLE_STANDARD_ARGS( JSON-C DEFAULT_MSG
        JSON-C_INCLUDE_DIR
        JSON-C_LIBRARY
        )

IF( JSON-C_FOUND )
    SET( JSON-C_INCLUDE_DIRS ${JSON-C_INCLUDE_DIR} )
    SET( JSON-C_LIBRARIES ${JSON-C_LIBRARY} )

    MARK_AS_ADVANCED(
            JSON-C_LIBRARY
            JSON-C_INCLUDE_DIR
            JSON-C_DIR
    )
ELSE()
    SET( JSON-C_DIR "" CACHE STRING
            "An optional hint to a directory for finding `json-c`"
            )
ENDIF()