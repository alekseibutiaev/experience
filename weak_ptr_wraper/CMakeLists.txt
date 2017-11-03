cmake_minimum_required (VERSION 3.5.0)

project (weak_ptr_wraper)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -std=c++11 -g3 -O0 -Wall -Werror -pthread")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -std=c++11 -g0 -O3 -Wall -Werror -pthread")

set(CMAKE_LIBRARY_ARCHITECTURE x86_64-linux-gnu)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

add_definitions( -DSTRING_DEFENITION="test string" )

#	message(FATAL_ERROR  ${Boost_LIBRARIES})


if(Boost_FOUND)
	include_directories( ${Boost_INCLUDE_DIR} )
	add_executable(weak_ptr_wraper weak_ptr_wraper.cpp)
	target_link_libraries( weak_ptr_wraper ${CMAKE_THREAD_LIBS_INIT} )
endif()
	
