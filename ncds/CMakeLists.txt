cmake_minimum_required(VERSION 3.5)
project("ncsdexample")
#set (CMAKE_CXX_STANDARD 17)

set(CXX_FLAGS_COMMON "-std=c++17")

set(CXX_FLAGS_DEBUG "-O0 -g3")
set(CXX_FLAGS_RELEASE "-O3 -g0")


set(CMAKE_CXX_FLAGS_DEBUG "${CXX_FLAGS_COMMON} ${CXX_FLAGS_DEBUG}")
set(CMAKE_CXX_FLAGS_RELEASE "${CXX_FLAGS_COMMON} ${CXX_FLAGS_RELEASE}")

include(FindPkgConfig)

option(AVROCPP_HOME "use home for avrocpp")
option(RDKAFKA_HOME "use home for rdkafka")
option(SPDLOG_HOME "use home for spdlog")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules/")
set(NLOCHMANN_MODULE_PATH "/usr/share/cmake-${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}/Modules/nlohmann_json")

message("Modules: " ${NLOCHMANN_MODULE_PATH})
message("VERSION: " "${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION}")

find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)

if(OPENSSL_FOUND)
  message(STATUS "OpenSSL Found: ${OPENSSL_VERSION}")
  message(STATUS "OpenSSL Include: ${OPENSSL_INCLUDE_DIR}")
  message(STATUS "OpenSSL Libraries: ${OPENSSL_LIBRARIES}")
endif()

find_package(AVROCPP QUIET)
find_package(RDKAFKA QUIET)
find_package(RDKAFKACPP QUIET)
find_package(JSON-C REQUIRED)
find_package(nlohmann_json REQUIRED CONFIG PATHS ${NLOCHMANN_MODULE_PATH})
#find_package(nlohmann_json REQUIRED)

set(JSON-C_INCLUDE_DIRSN ${JSON-C_INCLUDE_DIRS})
set(JSON-C_LIBRARIESN ${JSON-C_LIBRARIES})

message("AVROCPP_FOUND: " ${AVROCPP_FOUND})
message("AVROCPP_INCLUDE_DIR: " ${AVROCPP_INCLUDE_DIR})
message("AVROCPP_LIBRARIES: " ${AVROCPP_LIBRARIES})
message("RDKAFKA_FOUND: " ${RDKAFKA_FOUND})
message("RDKAFKA_INCLUDE_DIR: " ${RDKAFKA_INCLUDE_DIR})
message("RDKAFKA_LIBRARIES: " ${RDKAFKA_LIBRARIES})
message("RDKAFKACPP_FOUND: " ${RDKAFKACPP_FOUND})
message("RDKAFKACPP_INCLUDE_DIR: " ${RDKAFKACPP_INCLUDE_DIR})
message("RDKAFKACPP_LIBRARIES: " ${RDKAFKACPP_LIBRARIES})
message("JSON-C_INCLUDE_DIRS: " ${JSON-C_INCLUDE_DIRN})
message("JSON-C_LIBRARIES: " ${JSON-C_LIBRARIESN})

#add_subdirectory(library)
add_subdirectory(nasdaq)
add_subdirectory(avrotest)
add_subdirectory(kafkatest)

