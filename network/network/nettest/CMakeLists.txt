#file(GLOB HEADER_FILES *.h *.hpp)
#file(GLOB SOURCE_FILES *.cpp)

project(nettest)

include_directories(
  ${PROJECT_DIR}
  ${Boost_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME}_server server.cpp)

target_link_libraries(${PROJECT_NAME}_server
  network_static
  ${Boost_LIBRARIES}
  pthread
)

add_executable(${PROJECT_NAME}_client client.cpp)

target_link_libraries(${PROJECT_NAME}_client
  network_static
  ${Boost_LIBRARIES}
  pthread
)
