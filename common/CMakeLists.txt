cmake_minimum_required(VERSION 3.5)

project(common)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3 -std=c++11 -Wall -Werror -pthread")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g0 -std=c++11 -Wall -Werror -pthread")

set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})

message(${PROJECT} " SOURCES_DIR: " ${PROJECT_DIR})

add_subdirectory(src)
