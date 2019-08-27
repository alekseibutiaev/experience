FILE(GLOB HEADER_FILES *.h *.hpp)
FILE(GLOB SOURCE_FILES *.cpp)

include_directories(
  ${PROJECT_DIR}
  ${Boost_INCLUDE_DIRS}

)

add_executable(nettest ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(nettest
  network_static
  ${Boost_LIBRARIES}
  pthread
)
