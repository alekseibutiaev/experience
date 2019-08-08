cmake_minimum_required(VERSION 3.5)

project(network)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3 -std=c++11 -Wall -Werror")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g0 -std=c++11 -Wall -Werror")

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message("network SOURCES_DIR: " ${PROJECT_DIR})

find_package(Boost 1.55 REQUIRED COMPONENTS system)
#unit_test_framework

#Boost_FOUND            - True if headers and requested libraries were found
message("Boost_FOUND " ${Boost_FOUND})
#Boost_INCLUDE_DIRS     - Boost include directories
message("Boost_INCLUDE_DIRS " ${Boost_INCLUDE_DIRS})
#Boost_LIBRARY_DIRS     - Link directories for Boost libraries
message("Boost_LIBRARY_DIRS " ${Boost_LIBRARY_DIRS})
#Boost_LIBRARIES        - Boost component libraries to be linked
message("Boost_LIBRARIES " ${Boost_LIBRARIES})

add_subdirectory(src)
add_subdirectory(nettest)
