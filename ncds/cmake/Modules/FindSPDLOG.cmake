INCLUDE( FindPackageHandleStandardArgs )

# Checks an environment variable; note that the first check
# does not require the usual CMake $-sign.
IF(SPDLOG_DIR)
    message("SPDLOG_DIR was defined: " ${SPDLOG_DIR})
ENDIF()

FIND_PATH(
        SPDLOG_INCLUDE_DIR
        spdlog/spdlog.h spdlog.h
        HINTS
        ${SPDLOG_DIR}/include
)

FIND_LIBRARY( SPDLOG_LIBRARY spdlog
        HINTS ${SPDLOG_DIR}/build)


FIND_PACKAGE_HANDLE_STANDARD_ARGS( SPDLOG DEFAULT_MSG
        SPDLOG_INCLUDE_DIR
        SPDLOG_LIBRARY
        )

IF( SPDLOG_FOUND )
    SET( SPDLOG_INCLUDE_DIRS ${SPDLOG_INCLUDE_DIR} )
    SET( SPDLOG_LIBRARIES ${SPDLOG_LIBRARY} )

    MARK_AS_ADVANCED(
            SPDLOG_LIBRARY
            SPDLOG_INCLUDE_DIR
            SPDLOG_DIR
    )
ELSE()
    SET( SPDLOG_DIR "" CACHE STRING
            "An optional hint to a directory for finding `spdlog`"
            )
ENDIF()