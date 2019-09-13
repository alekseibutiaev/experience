file(GLOB HEADER_FILES *.h *.hpp)
file(GLOB SOURCE_FILES *.cpp)

project(nettest)

include_directories(
  ${PROJECT_DIR}
  ${Boost_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
  network_static
  ${Boost_LIBRARIES}
  pthread
)
