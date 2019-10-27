project(v8_base_without_compiler6)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti -Wno-return-type -Wno-comment -Wno-unused-function -Wno-maybe-uninitialized -Wno-deprecated-declarations")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON} -O0 -g3")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON} -O3 -g0")


include_directories(
  ${v8source}
  ${v8source}/include/
  ${v8source}/src
  ${CMAKE_BINARY_DIR}/v8build
  ${CMAKE_BINARY_DIR}/v8build/gen
  ${ICU_INCLUDE_DIRS}
)

set(${PROJECT_NAME}_sources
  ${v8source}/src/objects/js-date-time-format.cc
  ${v8source}/src/objects/js-list-format.cc
  ${v8source}/src/objects/js-locale.cc
  ${v8source}/src/objects/js-number-format.cc
  ${v8source}/src/objects/js-objects.cc
  ${v8source}/src/objects/js-plural-rules.cc
  ${v8source}/src/objects/js-regexp.cc
  ${v8source}/src/objects/js-relative-time-format.cc
  ${v8source}/src/objects/js-segmenter.cc
  ${v8source}/src/objects/js-segment-iterator.cc
  ${v8source}/src/objects/keys.cc
  ${v8source}/src/objects/layout-descriptor.cc
  ${v8source}/src/objects/literal-objects.cc
  ${v8source}/src/objects/lookup-cache.cc
  ${v8source}/src/objects/lookup.cc
  ${v8source}/src/objects/managed.cc
  ${v8source}/src/objects/map.cc
  ${v8source}/src/objects/map-updater.cc
  ${v8source}/src/objects/module.cc
  ${v8source}/src/objects/objects.cc
  ${v8source}/src/objects/ordered-hash-table.cc
  ${v8source}/src/objects/osr-optimized-code-cache.cc
  ${v8source}/src/objects/property.cc
  ${v8source}/src/objects/property-descriptor.cc
  ${v8source}/src/objects/scope-info.cc
  ${v8source}/src/objects/source-text-module.cc
  ${v8source}/src/objects/stack-frame-info.cc
  ${v8source}/src/objects/string.cc
  ${v8source}/src/objects/string-comparator.cc
  ${v8source}/src/objects/synthetic-module.cc
  ${v8source}/src/objects/tagged-impl.cc
  ${v8source}/src/objects/template-objects.cc
  ${v8source}/src/objects/transitions.cc
  ${v8source}/src/objects/type-hints.cc
  ${v8source}/src/objects/value-serializer.cc
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

