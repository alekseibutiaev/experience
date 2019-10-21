FILE(GLOB HEADER_FILES *.h *.hpp)
FILE(GLOB SOURCE_FILES *.cpp)

project(test1)

include_directories(
  ${SOLUTION_DIR}
  ${PROJECT_DIR}
  ${PUGIXML_INCLUDE_DIR}
)

link_directories(
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
  ${PUGIXML_LIBRARIES}
  Threads::Threads
)