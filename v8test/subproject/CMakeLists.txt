set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
message("SOURCES_DIR: " ${PROJECT_DIR})
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules/")

# 11 14 17
#set(CMAKE_CXX_STANDARD 11)

option(USE_WERROR "use cpp options -Werror" ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CXX_FLAGS_COMMON "-std=c++11 -Wall")

if(DEFINED USE_WERROR)
  set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -Werror")
endif()

set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON} -O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON} -O3 -g0")


set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

find_package(ICU 64.0 COMPONENTS i18n uc REQUIRED)
if(ICU_FOUND)
    message("ICU_FOUND: " ${ICU_FOUND})
    message("ICU_VERSION: " ${ICU_VERSION})
    message("ICU_INCLUDE_DIRS: " ${ICU_INCLUDE_DIRS})
    message("ICU_LIBRARIES: " ${ICU_LIBRARIES})
else()
    message (FATAL_ERROR "Cannot find ICU")
    message (FATAL_ERROR "for install read this https://kifarunix.com/how-to-install-php-7-3-3-on-ubuntu-18-04/")
    message (FATAL_ERROR "apt-get install libicu-dev")
endif()

set(Boost_USE_STATIC_LIBS        ON)
find_package(Boost 1.55 REQUIRED COMPONENTS system)
#unit_test_framework

message("Boost_FOUND " ${Boost_FOUND})
message("Boost_INCLUDE_DIRS " ${Boost_INCLUDE_DIRS})
message("Boost_LIBRARY_DIRS " ${Boost_LIBRARY_DIRS})
message("Boost_LIBRARIES " ${Boost_LIBRARIES})

find_package(V8 REQUIRED)
message("V8_FOUND: " ${V8_FOUND})
message("V8_INCLUDE_DIR: " ${V8_INCLUDE_DIR})
message("V8_LIBRARIES: " ${V8_LIBRARIES})

message("CXX_FLAGS_DEBUG: " ${CMAKE_CXX_FLAGS_DEBUG})
message("CXX_FLAGS_RELEASE: " ${CMAKE_CXX_FLAGS_RELEASE})

add_subdirectory(test1)
add_subdirectory(test2)
add_subdirectory(test3)
add_subdirectory(test4)

