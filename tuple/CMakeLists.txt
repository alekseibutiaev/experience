#-DCMAKE_BUILD_TYPE=
cmake_minimum_required (VERSION 3.5.0)

project (tuple)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -std=c++11 -g3 -O0 -Wall -Werror -pthread")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -std=c++11 -g0 -O3 -Wall -Werror -pthread")

set(CMAKE_LIBRARY_ARCHITECTURE x86_64-linux-gnu)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

add_definitions( -DSTRING_DEFENITION="test string" )

include_directories (
  ${PROJECT_SOURCE_DIR}
  ${PROJECT_SOURCE_DIR}/..
)

#	message(FATAL_ERROR  ${Boost_LIBRARIES})


if(Boost_FOUND)
	include_directories( ${Boost_INCLUDE_DIR} )
	add_executable( tuple tuple.cpp)
	target_link_libraries( tuple ${CMAKE_THREAD_LIBS_INIT} )
endif()
	
