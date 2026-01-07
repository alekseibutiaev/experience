FILE(GLOB HEADER_FILES *.h *.hpp)
FILE(GLOB SOURCE_FILES *.cpp)

project(test3)

add_definitions(-D__SCRIPT_NAME__="${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.js")

include_directories(
  ${SOLUTION_DIR}
  ${PROJECT_DIR}
  ${V8_INCLUDE_DIR}
  ${V8_INCLUDE_DIR}/v8
  ${ICU_INCLUDE_DIRS}
)

#link_directories(
#  ${Boost_LIBRARY_DIRS}
#)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
  ${V8_LIBRARIES}
  ${ICU_LIBRARIES}
  ${Boost_LIBRARIES}
  Threads::Threads
)