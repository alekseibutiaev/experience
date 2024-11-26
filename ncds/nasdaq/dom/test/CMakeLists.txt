file(GLOB headers *.h *.hpp)
file(GLOB sources *.cpp)

project(domtest)

add_executable(${PROJECT_NAME} ${sources})

target_include_directories(${PROJECT_NAME} PRIVATE ${Boost_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} nasdaq_static ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(NAME test1 COMMAND ${PROJECT_NAME})
