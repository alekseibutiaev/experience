cmake_minimum_required(VERSION 3.5)
project("ncsdexample")
include(FindPkgConfig)

option(AVROCPP_HOME "use home for avrocpp")
option(RDKAFKA_HOME "use home for rdkafka")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")

find_package(CURL REQUIRED)

find_package(AVROCPP QUIET)
find_package(RDKAFKA QUIET)
find_package(RDKAFKACPP QUIET)

message("AVROCPP_FOUND: " ${AVROCPP_FOUND})
message("AVROCPP_INCLUDE_DIR: " ${AVROCPP_INCLUDE_DIR})
message("AVROCPP_LIBRARIES: " ${AVROCPP_LIBRARIES})
message("RDKAFKA_FOUND: " ${RDKAFKA_FOUND})
message("RDKAFKA_INCLUDE_DIR: " ${RDKAFKA_INCLUDE_DIR})
message("RDKAFKA_LIBRARIES: " ${RDKAFKA_LIBRARIES})
message("RDKAFKACPP_FOUND: " ${RDKAFKACPP_FOUND})
message("RDKAFKACPP_INCLUDE_DIR: " ${RDKAFKACPP_INCLUDE_DIR})
message("RDKAFKACPP_LIBRARIES: " ${RDKAFKACPP_LIBRARIES})

add_subdirectory(library)
add_subdirectory(example)

