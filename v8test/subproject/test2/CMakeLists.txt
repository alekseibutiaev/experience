FILE(GLOB HEADER_FILES *.h *.hpp)
FILE(GLOB SOURCE_FILES *.cpp)

project(test2)

include_directories(
  ${SOLUTION_DIR}
  ${PROJECT_DIR}
  ${Boost_INCLUDE_DIRS}
  ${V8_INCLUDE_DIR}
  ${V8_INCLUDE_DIR}/v8
)

#link_directories(
#  ${Boost_LIBRARY_DIRS}
#)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
  ${V8_LIBRARIES}
#  /opt/v8lib/lib/x86_64-linux-gnu/v8/libv8_libplatform.a
#  /opt/v8lib/lib/x86_64-linux-gnu/v8/libv8.a
  ${ICU_LIBRARIES}
  ${Boost_LIBRARIES}
  Threads::Threads
)