project(v8_base_without_compiler3)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti -Wno-return-type -Wno-comment -Wno-unused-function -Wno-maybe-uninitialized -Wno-deprecated-declarations")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON} -O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON} -O3 -g0 -DNDEBUG")

include_directories(
  ${v8source}
  ${v8source}/include/
  ${v8source}/src
  ${CMAKE_BINARY_DIR}/v8build
  ${CMAKE_BINARY_DIR}/v8build/gen
  ${ICU_INCLUDE_DIRS}
)

set(${PROJECT_NAME}_sources
  ${v8source}/src/execution/thread-id.cc
  ${v8source}/src/execution/thread-local-top.cc
  ${v8source}/src/execution/v8threads.cc
  ${v8source}/src/extensions/cputracemark-extension.cc
  ${v8source}/src/extensions/externalize-string-extension.cc
  ${v8source}/src/extensions/free-buffer-extension.cc
  ${v8source}/src/extensions/gc-extension.cc
  ${v8source}/src/extensions/ignition-statistics-extension.cc
  ${v8source}/src/extensions/statistics-extension.cc
  ${v8source}/src/extensions/trigger-failure-extension.cc
  ${v8source}/src/flags/flags.cc
  ${v8source}/src/handles/global-handles.cc
  ${v8source}/src/handles/handles.cc
  ${v8source}/src/heap/array-buffer-collector.cc
  ${v8source}/src/heap/array-buffer-tracker.cc
  ${v8source}/src/heap/basic-memory-chunk.cc
  ${v8source}/src/heap/code-stats.cc
  ${v8source}/src/heap/combined-heap.cc
  ${v8source}/src/heap/concurrent-marking.cc
  ${v8source}/src/heap/embedder-tracing.cc
  ${v8source}/src/heap/factory.cc
  ${v8source}/src/heap/gc-idle-time-handler.cc
  ${v8source}/src/heap/gc-tracer.cc
  ${v8source}/src/heap/heap.cc
  ${v8source}/src/heap/heap-controller.cc
  ${v8source}/src/heap/incremental-marking.cc
  ${v8source}/src/heap/incremental-marking-job.cc
  ${v8source}/src/heap/invalidated-slots.cc
  ${v8source}/src/heap/item-parallel-job.cc
  ${v8source}/src/heap/mark-compact.cc
  ${v8source}/src/heap/marking.cc
  ${v8source}/src/heap/memory-measurement.cc
  ${v8source}/src/heap/memory-reducer.cc
  ${v8source}/src/heap/object-stats.cc
)

add_definitions(-DENABLE_MINOR_MC)
add_definitions(-DVERIFY_HEAP)
add_definitions(-DV8_INTL_SUPPORT)
add_definitions(-DV8_31BIT_SMIS_ON_64BIT_ARCH)
add_definitions(-DV8_HAVE_TARGET_OS)
add_definitions(-DV8_TARGET_OS_LINUX)

if(${ARCHITECTURE} STREQUAL "x86_64")
  add_definitions(-DV8_TARGET_ARCH_X64)
elseif(${ARCHITECTURE} STREQUAL "i386" OR ${ARCHITECTURE} STREQUAL "i486" OR ${ARCHITECTURE} STREQUAL "i586"  OR ${ARCHITECTURE} STREQUAL "i686")
  add_definitions(V8_TARGET_ARCH_IA32)
endif()

add_library(${PROJECT_NAME}_obj OBJECT ${${PROJECT_NAME}_sources})

add_library(${PROJECT_NAME}_obj_pic OBJECT ${${PROJECT_NAME}_sources})
set_property(TARGET ${PROJECT_NAME}_obj_pic PROPERTY POSITION_INDEPENDENT_CODE 1)

add_dependencies(${PROJECT_NAME}_obj
  rename_debug
  bytecodes-builtins-list
  tq_files
)

add_dependencies(${PROJECT_NAME}_obj_pic
  rename_debug
  bytecodes-builtins-list
  tq_files
)

