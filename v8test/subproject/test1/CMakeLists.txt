FILE(GLOB HEADER_FILES *.h *.hpp)
FILE(GLOB SOURCE_FILES *.cpp)

project(executable)

include_directories(
  ${SOLUTION_DIR}
  /home/butiaev/project/toshiba/v8install/v8/include
  ${Boost_INCLUDE_DIRS}
)

link_directories(
  ${Boost_LIBRARY_DIRS}
)

add_executable(${PROJECT_NAME} ${HEADER_FILES} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME}
  ${Boost_LIBRARIES}
  /home/butiaev/project/toshiba/v8install/v8/out/x64.release.old/libc++.so
  /home/butiaev/project/toshiba/v8install/v8/out/x64.release.old/libv8.so
  /home/butiaev/project/toshiba/v8install/v8/out/x64.release.old/libv8_libplatform.so
  Threads::Threads
)