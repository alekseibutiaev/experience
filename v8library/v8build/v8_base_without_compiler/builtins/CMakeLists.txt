project(builtins)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti -Wno-return-type -Wno-comment\
    -Wno-unused-function -Wno-strict-aliasing")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON}")

include_directories(
  ${v8source}
  ${v8source}/include/
  ${v8source}/src
  ${CMAKE_BINARY_DIR}/v8build
  ${CMAKE_BINARY_DIR}/v8build/gen
  ${ICU_INCLUDE_DIRS}
)

set(${PROJECT_NAME}_headers
  ${v8source}/src/builtins/accessors.h
  ${v8source}/src/builtins/builtins-constructor.h
  ${v8source}/src/builtins/builtins-definitions.h
  ${v8source}/src/builtins/builtins-descriptors.h
  ${v8source}/src/builtins/builtins-promise.h
  ${v8source}/src/builtins/builtins-utils-inl.h
  ${v8source}/src/builtins/builtins-utils.h
  ${v8source}/src/builtins/builtins.h
  ${v8source}/src/builtins/constants-table-builder.h
)

set(${PROJECT_NAME}_sources
  ${v8source}/src/builtins/accessors.cc
  ${v8source}/src/builtins/builtins-api.cc
  ${v8source}/src/builtins/builtins-array.cc
  ${v8source}/src/builtins/builtins-arraybuffer.cc
  ${v8source}/src/builtins/builtins-async-module.cc
  ${v8source}/src/builtins/builtins-bigint.cc
  ${v8source}/src/builtins/builtins-call.cc
  ${v8source}/src/builtins/builtins-callsite.cc
  ${v8source}/src/builtins/builtins-collections.cc
  ${v8source}/src/builtins/builtins-console.cc
  ${v8source}/src/builtins/builtins-dataview.cc
  ${v8source}/src/builtins/builtins-date.cc
  ${v8source}/src/builtins/builtins-error.cc
  ${v8source}/src/builtins/builtins-extras-utils.cc
  ${v8source}/src/builtins/builtins-function.cc
  ${v8source}/src/builtins/builtins-global.cc
  ${v8source}/src/builtins/builtins-internal.cc
  ${v8source}/src/builtins/builtins-intl.cc
  ${v8source}/src/builtins/builtins-json.cc
  ${v8source}/src/builtins/builtins-number.cc
  ${v8source}/src/builtins/builtins-object.cc
  ${v8source}/src/builtins/builtins-promise.cc
  ${v8source}/src/builtins/builtins-reflect.cc
  ${v8source}/src/builtins/builtins-regexp.cc
  ${v8source}/src/builtins/builtins-sharedarraybuffer.cc
  ${v8source}/src/builtins/builtins-string.cc
  ${v8source}/src/builtins/builtins-symbol.cc
  ${v8source}/src/builtins/builtins-trace.cc
  ${v8source}/src/builtins/builtins-typed-array.cc
  ${v8source}/src/builtins/builtins-weak-refs.cc
  ${v8source}/src/builtins/builtins.cc
  ${v8source}/src/builtins/constants-table-builder.cc)

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
add_definitions(-DBUILDING_V8_SHARED)
add_definitions(-DV8_TARGET_OS_LINUX)
add_definitions(-DV8_ENABLE_LAZY_SOURCE_POSITIONS)
add_definitions(-DV8_INTL_SUPPORT)
add_definitions(-DV8_WIN64_UNWINDING_INFO)
add_definitions(-DV8_HAVE_TARGET_OS)
add_definitions(-D_GNU_SOURCE)
add_definitions(-DENABLE_DISASSEMBLER)

if(${ARCHITECTURE} STREQUAL "x86_64")
  add_definitions(-DV8_TARGET_ARCH_X64)
elseif(${ARCHITECTURE} STREQUAL "i386" OR ${ARCHITECTURE} STREQUAL "i486" OR ${ARCHITECTURE} STREQUAL "i586"  OR ${ARCHITECTURE} STREQUAL "i686")
  add_definitions(V8_TARGET_ARCH_IA32)
endif()

add_library(${PROJECT_NAME}_obj OBJECT ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

add_library(${PROJECT_NAME}_obj_pic OBJECT ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})
set_property(TARGET ${PROJECT_NAME}_obj_pic PROPERTY POSITION_INDEPENDENT_CODE 1)

add_dependencies(${PROJECT_NAME}_obj
  rename_debug
  bytecodes-builtins-list
  run_torque
)

add_dependencies(${PROJECT_NAME}_obj_pic
  rename_debug
  bytecodes-builtins-list
  run_torque
)

