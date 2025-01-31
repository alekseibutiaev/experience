cmake_minimum_required(VERSION 3.15)
project("ncsdexample")
#set (CMAKE_CXX_STANDARD 17)

set(CXX_FLAGS_COMMON "-std=c++17  -Wall -Werror")

set(CMAKE_THREAD_LIBS_INIT "-lpthread")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pthread")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
set(CMAKE_HAVE_THREADS_LIBRARY 1)
set(CMAKE_USE_PTHREADS_INIT 1)
set(THREADS_PREFER_PTHREAD_FLAG ON)

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

find_package(PkgConfig REQUIRED)
find_package(Threads REQUIRED)
find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)

if(OPENSSL_FOUND)
  message(STATUS "OpenSSL Found: ${OPENSSL_VERSION}")
  message(STATUS "OpenSSL Include: ${OPENSSL_INCLUDE_DIR}")
  message(STATUS "OpenSSL Libraries: ${OPENSSL_LIBRARIES}")
endif()

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost 1.65 REQUIRED COMPONENTS filesystem iostreams program_options regex system unit_test_framework)

find_package(ZLIB REQUIRED)
find_package(AVROCPP QUIET)
find_package(JSON-C REQUIRED)
find_package(nlohmann_json REQUIRED CONFIG PATHS ${NLOCHMANN_MODULE_PATH})

pkg_search_module(RDKAFKA QUIET rdkafka)
pkg_search_module(RDKAFKACPP QUIET rdkafka++)

set(JSON-C_INCLUDE_DIRSN ${JSON-C_INCLUDE_DIRS})
set(JSON-C_LIBRARIESN ${JSON-C_LIBRARIES})

message("Boost_VERSION: " ${Boost_VERSION})
message("Boost_INCLUDE_DIRS: " ${Boost_INCLUDE_DIRS})
message("Boost_LIBRARY_DIRS: " ${Boost_LIBRARY_DIRS})

message("ZLIB_FOUND: " ${ZLIB_FOUND})
message("ZLIB_INCLUDE_DIR: " ${ZLIB_INCLUDE_DIR})
message("ZLIB_LIBRARIES: " ${ZLIB_LIBRARIES})

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

add_subdirectory(nasdaq)
add_subdirectory(avrotest)
add_subdirectory(kafkatest)
