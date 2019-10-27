project(v8_base_without_compiler5)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti -Wno-return-type -Wno-comment -Wno-unused-function -Wno-deprecated-declarations")

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
  ${v8source}/src/interpreter/constant-array-builder.cc
  ${v8source}/src/interpreter/control-flow-builders.cc
  ${v8source}/src/interpreter/handler-table-builder.cc
  ${v8source}/src/interpreter/interpreter.cc
  ${v8source}/src/interpreter/interpreter-intrinsics.cc
  ${v8source}/src/json/json-parser.cc
  ${v8source}/src/json/json-stringifier.cc
  ${v8source}/src/logging/counters.cc
  ${v8source}/src/logging/log.cc
  ${v8source}/src/logging/log-utils.cc
  ${v8source}/src/numbers/bignum.cc
  ${v8source}/src/numbers/bignum-dtoa.cc
  ${v8source}/src/numbers/cached-powers.cc
  ${v8source}/src/numbers/conversions.cc
  ${v8source}/src/numbers/diy-fp.cc
  ${v8source}/src/numbers/dtoa.cc
  ${v8source}/src/numbers/fast-dtoa.cc
  ${v8source}/src/numbers/fixed-dtoa.cc
  ${v8source}/src/numbers/math-random.cc
  ${v8source}/src/numbers/strtod.cc
  ${v8source}/src/objects/backing-store.cc
  ${v8source}/src/objects/bigint.cc
  ${v8source}/src/objects/code.cc
  ${v8source}/src/objects/contexts.cc
  ${v8source}/src/objects/debug-objects.cc
  ${v8source}/src/objects/elements.cc
  ${v8source}/src/objects/elements-kind.cc
  ${v8source}/src/objects/embedder-data-array.cc
  ${v8source}/src/objects/feedback-vector.cc
  ${v8source}/src/objects/field-type.cc
  ${v8source}/src/objects/intl-objects.cc
  ${v8source}/src/objects/js-array-buffer.cc
  ${v8source}/src/objects/js-break-iterator.cc
  ${v8source}/src/objects/js-collator.cc
)

add_definitions(-DV8_USE_EXTERNAL_STARTUP_DATA)
add_definitions(-DV8_ENABLE_REGEXP_INTERPRETER_THREADED_DISPATCH)
add_definitions(-D__STDC_CONSTANT_MACROS)
add_definitions(-DV8_DEPRECATION_WARNINGS)
add_definitions(-DV8_EMBEDDED_BUILTINS)
add_definitions(-DENABLE_GDB_JIT_INTERFACE)
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

