FILE(GLOB HEADER_FILES *.h *.hpp)
FILE(GLOB SOURCE_FILES *.cpp)

project(executable)

include_directories(
  ${SOLUTION_DIR}
  ${PROJECT_DIR}
  ${Boost_INCLUDE_DIRS}
)

link_directories(
  ${Boost_LIBRARY_DIRS}
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
  fixed_static
  ${Boost_LIBRARIES}
  Threads::Threads
)