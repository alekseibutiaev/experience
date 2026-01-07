cmake_minimum_required (VERSION 3.5.0)

project (booststrand)

set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -std=c++11 -g3 -o0 -pthread")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -std=c++11 -g0 -o3 -pthread")

set(CMAKE_LIBRARY_ARCHITECTURE x86_64-linux-gnu)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_DETAILED_FAILURE_MSG TRUE)
set(Boost_USE_STATIC_RUNTIME ON)


#find_package(Boost 1.58.0 REQUIRED COMPONENTS system)
#find_package(Boost 1.58.0 COMPONENTS system )
find_package(Threads REQUIRED)
find_package(Boost REQUIRED)

add_definitions( -DSTRING_DEFENITION="test string" )

#	message(FATAL_ERROR  ${Boost_LIBRARIES})


if(Boost_FOUND)
	include_directories( ${Boost_INCLUDE_DIR} )
	add_executable(booststrand booststrand.cpp)
	target_link_libraries( booststrand boost_system pthread )
endif()
	
