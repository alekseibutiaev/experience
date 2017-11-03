# some comment

cmake_minimum_required (VERSION 2.6) 

cmake_policy(SET CMP0011 NEW)
cmake_policy(SET CMP0003 OLD)

OPTION(WITH_DEBUG_MODE "Build with debug mode" ON)

if ( NOT UNIX )
    message (FATAL_ERROR "Not Unix!")
endif ()

message ("Starting cmake")

# я вынес настройки путей, флаги компиляции в отдельный фаил, чтобы не громоздить здесь лишнего
#include (myproj.cmake)

# создаём новый проект
set (PROJECT myproj)

# в текущем проекте ничего не нужно дополнительно компилировать
set (LIBRARIES)
# следующий код нужен для компиляции и подключения сторонних библиотек 
    foreach (LIBRARY ${LIBRARIES})
        find_library("${LIBRARY}_FOUND" ${LIBRARY})
        message(STATUS "Check the ${LIBRARY} is installed: " ${${LIBRARY}_FOUND})
        if ( "${${LIBRARY}_FOUND}" STREQUAL "${LIBRARY}_FOUND-NOTFOUND" )
            message(STATUS "Adding library sources")
            add_subdirectory (../${LIBRARY} lib/${LIBRARY})
        endif ()
    endforeach ()

# никаких дополнительных целей нет
set (TARGETS "")

set (HEADERS "")

message ( STATUS "SOURCES: ${SOURCES}")

add_subdirectory (src)

set ("${PROJECT}_BINARY_DIR"  bin)
set ("${PROJECT}_SOURCE_DIR" src:include)
set ("${PROJECT}_LIB_DIR" lib)

set (CMAKE_INCLUDE_PATH ${${PROJECT}_SOURCE_DIR})
set (CMAKE_LIBRARY_PATH ${${PROJECT}_LIB_DIR})
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${${PROJECT}_BINARY_DIR})
set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_BUILD_TYPE Debug)

set(CMAKE_CXX_FLAGS)

set (ERR_NO_UNIX "Cannot build on non Unix systems")

if ( WITH_DEBUG_MODE )
     ADD_DEFINITIONS( -DMY_DEBUG_MODE=1)
endif()

if ( CMAKE_COMPILER_IS_GNUCXX )
		message ( STATUS "GNU compuler")
    set(MY_CXX_FLAGS  "-Wall -fmessage-length=0 -v")
    set(CMAKE_CXX_FLAGS "-O0 -std=c++11 ${MY_CXX_FLAGS}")
    # я отключил настройку разных флагов для релиза и отладки. Пока что не нужно.
    #set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -fno-reorder-blocks -fno-schedule-insns -fno-inline")
    #set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
else ()
    message (FATAL_ERROR ${ERR_NO_UNIX})
endif ()

message (STATUS ${CMAKE_CXX_FLAGS})



