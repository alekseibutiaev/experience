project(d8)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti -Wno-comment")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON} -O3 -g0")

include_directories(
  ${v8source}
  ${v8source}/include
  ${CMAKE_BINARY_DIR}/v8build/gen
)

set(${PROJECT_NAME}_sources
  ${v8source}/src/d8/async-hooks-wrapper.cc
  ${v8source}/src/d8/d8-console.cc
  ${v8source}/src/d8/d8-js.cc
  ${v8source}/src/d8/d8-platforms.cc
  ${v8source}/src/d8/d8.cc
)

add_definitions(-DVERIFY_HEAP)
add_definitions(-DV8_31BIT_SMIS_ON_64BIT_ARCH)
add_definitions(-D_FILE_OFFSET_BITS=64)
add_definitions(-D_LARGEFILE64_SOURCE)
add_definitions(-DV8_HAVE_TARGET_OS)
add_definitions(-DV8_TARGET_OS_LINUX)

if(${CMAKE_SYSTEM_NAME} MATCHES 'Linux' )
  set(${PROJECT_NAME}_sources ${${PROJECT_NAME}_sources} ${v8source}/src/d8/d8-posix.cc)
else()
  set(${PROJECT_NAME}_sources ${${PROJECT_NAME}_sources} ${v8source}/src/d8/d8-windows.cc)
endif()

if(${ARCHITECTURE} STREQUAL "x86_64")
  add_definitions(-DV8_TARGET_ARCH_X64)
elseif(${ARCHITECTURE} STREQUAL "i386" OR ${ARCHITECTURE} STREQUAL "i486" OR ${ARCHITECTURE} STREQUAL "i586"  OR ${ARCHITECTURE} STREQUAL "i686")
  add_definitions(V8_TARGET_ARCH_IA32)
endif()

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

target_link_libraries(${PROJECT_NAME}
  v8
  v8_libplatform
  encoding_static
  ${ICU_LIBRARIES}
  pthread
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/d8
  DESTINATION bin
)

