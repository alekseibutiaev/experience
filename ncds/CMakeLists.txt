cmake_minimum_required(VERSION 3.5)
project("ncsdexample")
set (CMAKE_CXX_STANDARD 17)

include(FindPkgConfig)

option(AVROCPP_HOME "use home for avrocpp")
option(RDKAFKA_HOME "use home for rdkafka")
option(SPDLOG_HOME "use home for spdlog")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
set(NLOCHMANN_MODULE_PATH "/usr/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules/nlohmann_json")

message("Modules: " ${NLOCHMANN_MODULE_PATH})
message("VERSION: " "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}")

find_package(CURL REQUIRED)

find_package(AVROCPP QUIET)
find_package(RDKAFKA QUIET)
find_package(RDKAFKACPP QUIET)
find_package(JSON-C REQUIRED)
find_package(SPDLOG REQUIRED)
find_package(nlohmann_json REQUIRED CONFIG PATHS ${NLOCHMANN_MODULE_PATH})
#find_package(nlohmann_json REQUIRED)

message("AVROCPP_FOUND: " ${AVROCPP_FOUND})
message("AVROCPP_INCLUDE_DIR: " ${AVROCPP_INCLUDE_DIR})
message("AVROCPP_LIBRARIES: " ${AVROCPP_LIBRARIES})
message("RDKAFKA_FOUND: " ${RDKAFKA_FOUND})
message("RDKAFKA_INCLUDE_DIR: " ${RDKAFKA_INCLUDE_DIR})
message("RDKAFKA_LIBRARIES: " ${RDKAFKA_LIBRARIES})
message("RDKAFKACPP_FOUND: " ${RDKAFKACPP_FOUND})
message("RDKAFKACPP_INCLUDE_DIR: " ${RDKAFKACPP_INCLUDE_DIR})
message("RDKAFKACPP_LIBRARIES: " ${RDKAFKACPP_LIBRARIES})
message("JSON-C_INCLUDE_DIR: " ${JSON-C_INCLUDE_DIR})
message("JSON-C_LIBRARY: " ${JSON-C_LIBRARY})
message("SPDLOG_INCLUDE_DIR: " ${SPDLOG_INCLUDE_DIR})
message("SPDLOG_LIBRARY: " ${SPDLOG_LIBRARY})

add_subdirectory(library)
add_subdirectory(example)
add_subdirectory(kafka)
add_subdirectory(kafkatest)
