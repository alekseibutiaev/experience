file(GLOB headers *.h *.hpp)
file(GLOB sources *.cpp)

project(domtest)

add_executable(${PROJECT_NAME} ${sources})

target_link_libraries(${PROJECT_NAME} nasdaq_static   Boost::boost
  Boost::unit_test_framework

)

add_test(NAME test1 COMMAND ${PROJECT_NAME})
