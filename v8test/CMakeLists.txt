cmake_minimum_required(VERSION 3.5)

set(SOLUTION_DIR ${CMAKE_CURRENT_SOURCE_DIR})
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")

add_subdirectory(subproject)

