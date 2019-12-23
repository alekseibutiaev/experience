set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
message("template SOURCES_DIR: " ${PROJECT_DIR})

# 11 14 17
#set(CMAKE_CXX_STANDARD 11)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_RELEASE "")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g3 -pthread -std=c++11 -Wall")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -g0 -pthread -std=c++11 -Wall")

option(USE_WERROR ON)

option(PUGIXML_HOME "use home for pugixml")
option(QUICKFIX_HOME "use home for quikfix")

option(PUGIXML_STATIC "use static libpugixml" ON)
option(QUICKFIX_STATIC "use static quickfix" ON)

if(DEFINED USE_WERROR)
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Werror")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Werror")
endif()


message("CXX_FLAGS_DEBUG: " ${CMAKE_CXX_FLAGS_DEBUG})
message("CXX_FLAGS_RELEASE: " ${CMAKE_CXX_FLAGS_RELEASE})

set(Boost_USE_STATIC_LIBS        ON)

find_package(Threads REQUIRED)
find_package(Boost 1.55 REQUIRED)
#COMPONENTS system unit_test_framework

find_package(PugiXML REQUIRED)
find_package(QUICKFIX REQUIRED)


#Boost_FOUND            - True if headers and requested libraries were found
message("Boost_FOUND " ${Boost_FOUND})
#Boost_INCLUDE_DIRS     - Boost include directories
message("Boost_INCLUDE_DIRS " ${Boost_INCLUDE_DIRS})
#Boost_LIBRARY_DIRS     - Link directories for Boost libraries
message("Boost_LIBRARY_DIRS " ${Boost_LIBRARY_DIRS})
#Boost_LIBRARIES        - Boost component libraries to be linked
message("Boost_LIBRARIES " ${Boost_LIBRARIES})

message("PUGIXML_FOUND: " ${PUGIXML_FOUND})
message("PUGIXML_INCLUDE_DIR: " ${PUGIXML_INCLUDE_DIR})
message("PUGIXML_LIBRARIES: " ${PUGIXML_LIBRARIES})

message("QUICKFIX_FOUND: " ${QUICKFIX_FOUND})
message("QUICKFIX_INCLUDE_DIR: " ${QUICKFIX_INCLUDE_DIR})
message("QUICKFIX_LIBRARIES: " ${QUICKFIX_LIBRARIES})

add_subdirectory(fixmsg)
