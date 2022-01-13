set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
message("template SOURCES_DIR: " ${PROJECT_DIR})

option(USE_WERROR ON)

# 11 14 17
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CUSTOM_C_FLAGS ${CMAKE_C_FLAGS})
set(CUSTOM_CXX_FLAGS ${CMAKE_CXX_FLAGS})

set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "")

set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package (Threads REQUIRED)

if(CMAKE_USE_PTHREADS_INIT)
    set(CUSTOM_C_FLAGS ${CUSTOM_C_FLAGS} "-pthread")
    set(CUSTOM_CXX_FLAGS ${CUSTOM_CXX_FLAGS} "-pthread")
endif(CMAKE_USE_PTHREADS_INIT)

set(Boost_USE_STATIC_LIBS ON)
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

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CUSTOM_CXX_FLAGS} -O0 -g3 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CUSTOM_CXX_FLAGS} -O3 -g0 -Wall")

if(DEFINED USE_WERROR)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Werror")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Werror")
endif()

message("CXX_FLAGS_DEBUG: " ${CMAKE_CXX_FLAGS_DEBUG})
message("CXX_FLAGS_RELEASE: " ${CMAKE_CXX_FLAGS_RELEASE})

add_subdirectory(executable)
