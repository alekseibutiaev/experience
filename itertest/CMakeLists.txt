cmake_minimum_required(VERSION 3.15)
project(itertest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_FLAGS_DEBUG "-g3 -O0")
set(CMAKE_C_FLAGS_RELEASE "-g0 -O3")

#Bring the headers, such as Student.h into the project
#include_directories(include)

#Can manually add the sources using the set command as follows:
#set(SOURCES src/mainapp.cpp src/Student.cpp)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

