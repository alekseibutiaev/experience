set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
message("template SOURCES_DIR: " ${PROJECT_DIR})

# 11 14 17
#set(CMAKE_CXX_STANDARD 11)

option(USE_WERROR "use cpp options -Werror" ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CXX_FLAGS_COMMON "-std=c++11 -Wall")

set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON}  -O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON} -O3 -g0")

if(DEFINED USE_WERROR)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Werror")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Werror")
endif()


set(CMAKE_THREAD_PREFER_PTHREAD ON)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

set(Boost_USE_STATIC_LIBS        ON)
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

message("CXX_FLAGS_DEBUG: " ${CMAKE_CXX_FLAGS_DEBUG})
message("CXX_FLAGS_RELEASE: " ${CMAKE_CXX_FLAGS_RELEASE})


add_subdirectory(test1)
