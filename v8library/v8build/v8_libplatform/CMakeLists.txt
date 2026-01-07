project(v8_libplatform)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON} -O3 -g0")

include_directories(
  ${v8source}
  ${v8source}/include
  ${v8source}/src
  ${CMAKE_BINARY_DIR}/v8build
)

link_directories(
  ${Boost_LIBRARIES}
)

set(${PROJECT_NAME}_sources
  ${v8source}/src/libplatform/default-foreground-task-runner.cc
  ${v8source}/src/libplatform/default-platform.cc
  ${v8source}/src/libplatform/default-worker-threads-task-runner.cc
  ${v8source}/src/libplatform/delayed-task-queue.cc
  ${v8source}/src/libplatform/task-queue.cc
  ${v8source}/src/libplatform/tracing/trace-buffer.cc
  ${v8source}/src/libplatform/tracing/trace-config.cc
  ${v8source}/src/libplatform/tracing/trace-object.cc
  ${v8source}/src/libplatform/tracing/trace-writer.cc
  ${v8source}/src/libplatform/tracing/tracing-controller.cc
  ${v8source}/src/libplatform/worker-thread.cc
)

add_definitions(-DV8_USE_EXTERNAL_STARTUP_DATA)
add_definitions(-DV8_ENABLE_REGEXP_INTERPRETER_THREADED_DISPATCH)
add_definitions(-D__STDC_CONSTANT_MACROS)
add_definitions(-DV8_DEPRECATION_WARNINGS)
add_definitions(-DV8_SHARED_RO_HEAP)
add_definitions(-DUSING_V8_BASE_SHARED)
add_definitions(-DDISABLE_UNTRUSTED_CODE_MITIGATIONS)
add_definitions(-DV8_USE_SNAPSHOT)
add_definitions(-DENABLE_HANDLE_ZAPPING)
add_definitions(-DV8_31BIT_SMIS_ON_64BIT_ARCH)
add_definitions(-DOBJECT_PRINT)
add_definitions(-DENABLE_MINOR_MC)
add_definitions(-DVERIFY_HEAP)
add_definitions(-DV8_IMMINENT_DEPRECATION_WARNINGS)
add_definitions(-DNVALGRIND)
add_definitions(-DV8_TYPED_ARRAY_MAX_SIZE_IN_HEAP=64)
add_definitions(-D__STDC_FORMAT_MACROS)
add_definitions(-DV8_CONCURRENT_MARKING)
add_definitions(-DV8_TARGET_OS_LINUX)
add_definitions(-DV8_ENABLE_LAZY_SOURCE_POSITIONS)
add_definitions(-DV8_INTL_SUPPORT)
add_definitions(-DV8_WIN64_UNWINDING_INFO)
add_definitions(-DBUILDING_V8_PLATFORM_SHARED)
add_definitions(-DV8_HAVE_TARGET_OS)
add_definitions(-D_GNU_SOURCE)
add_definitions(-DUSING_V8_PLATFORM_SHARED)
add_definitions(-DENABLE_DISASSEMBLER)

if(${ARCHITECTURE} STREQUAL "x86_64")
  add_definitions(-DV8_TARGET_ARCH_X64)
  set(LIB_DESTINATION lib/x86_64-linux-gnu/)
elseif(${ARCHITECTURE} STREQUAL "i386" OR ${ARCHITECTURE} STREQUAL "i486" OR ${ARCHITECTURE} STREQUAL "i586"  OR ${ARCHITECTURE} STREQUAL "i686")
  add_definitions(V8_TARGET_ARCH_IA32)
  set(LIB_DESTINATION lib/i386-linux-gnu/)
endif()

add_library(${PROJECT_NAME}_obj OBJECT ${${PROJECT_NAME}_sources})
add_library(${PROJECT_NAME}_static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}_obj>)
set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

add_library(${PROJECT_NAME}_obj_pic OBJECT ${${PROJECT_NAME}_sources})
set_property(TARGET ${PROJECT_NAME}_obj_pic PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(${PROJECT_NAME}_static_pic STATIC $<TARGET_OBJECTS:${PROJECT_NAME}_obj_pic>)
add_library(${PROJECT_NAME} SHARED $<TARGET_OBJECTS:${PROJECT_NAME}_obj_pic>)

add_dependencies(${PROJECT_NAME}_obj
  bytecodes-builtins-list
)

add_dependencies(${PROJECT_NAME}_obj_pic
  bytecodes-builtins-list
)

install(FILES
  ${v8source}/include/libplatform/libplatform-export.h
  ${v8source}/include/libplatform/v8-tracing.h
  ${v8source}/include/libplatform/libplatform.h
  DESTINATION include/v8/libplatform
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/libv8_libplatform.a
  ${CMAKE_CURRENT_BINARY_DIR}/libv8_libplatform.so
  ${CMAKE_CURRENT_BINARY_DIR}/libv8_libplatform_static_pic.a
  DESTINATION ${LIB_DESTINATION}v8/
)

