#file(GLOB HEADER_FILES *.h *.hpp)
#file(GLOB SOURCE_FILES *.cpp)

project(nettest)

include_directories(
  ${PROJECT_DIR}
  ${Boost_INCLUDE_DIRS}
)

add_library(${PROJECT_NAME}_param OBJECT clparametrs.h clparametrs.cpp)

add_executable(${PROJECT_NAME}_server server.cpp $<TARGET_OBJECTS:${PROJECT_NAME}_param>)

target_link_libraries(${PROJECT_NAME}_server
  network_static
  ${Boost_LIBRARIES}
  Threads::Threads
)

add_executable(${PROJECT_NAME}_client client.cpp $<TARGET_OBJECTS:${PROJECT_NAME}_param>)

target_link_libraries(${PROJECT_NAME}_client
  network_static
  ${Boost_LIBRARIES}
  Threads::Threads
)
