FILE(GLOB HEADER_FILES *.h *.hpp)
FILE(GLOB SOURCE_FILES *.cpp)

project(fixmsg)

add_definitions(-DHAVE_STD_UNIQUE_PTR -DCPP_NOEXCEPT_FUNCTION_TYPE)

include_directories(
  ${CMAKE_CURRENT_DIR}
  ${SOLUTION_DIR}
  ${PROJECT_DIR}
  ${PUGIXML_INCLUDE_DIR}
  ${QUICKFIX_INCLUDE_DIR}
  ${Boost_INCLUDE_DIRS}
)

link_directories(
  ${Boost_LIBRARY_DIRS}
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})


target_link_libraries(${PROJECT_NAME}
  ${PUGIXML_LIBRARIES}
  ${QUICKFIX_LIBRARIES}
  ${Boost_LIBRARIES}
  Threads::Threads
)

