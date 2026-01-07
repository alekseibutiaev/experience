project(v8_initializers)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti -Wno-return-type\
    -Wno-comment -Wno-maybe-uninitialized")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON}")

include_directories(
  ${v8source}
  ${v8source}/include/
  ${v8source}/src
  ${CMAKE_BINARY_DIR}/v8build
  ${CMAKE_BINARY_DIR}/v8build/gen
)

set(${PROJECT_NAME}_sources
  ${v8source}/src/builtins/builtins-arguments-gen.cc
  ${v8source}/src/builtins/builtins-array-gen.cc
  ${v8source}/src/builtins/builtins-async-function-gen.cc
  ${v8source}/src/builtins/builtins-async-gen.cc
  ${v8source}/src/builtins/builtins-async-generator-gen.cc
  ${v8source}/src/builtins/builtins-async-iterator-gen.cc
  ${v8source}/src/builtins/builtins-bigint-gen.cc
  ${v8source}/src/builtins/builtins-boolean-gen.cc
  ${v8source}/src/builtins/builtins-call-gen.cc
  ${v8source}/src/builtins/builtins-collections-gen.cc
  ${v8source}/src/builtins/builtins-console-gen.cc
  ${v8source}/src/builtins/builtins-constructor-gen.cc
  ${v8source}/src/builtins/builtins-conversion-gen.cc
  ${v8source}/src/builtins/builtins-date-gen.cc
  ${v8source}/src/builtins/builtins-debug-gen.cc
  ${v8source}/src/builtins/builtins-function-gen.cc
  ${v8source}/src/builtins/builtins-generator-gen.cc
  ${v8source}/src/builtins/builtins-global-gen.cc
  ${v8source}/src/builtins/builtins-handler-gen.cc
  ${v8source}/src/builtins/builtins-ic-gen.cc
  ${v8source}/src/builtins/builtins-internal-gen.cc
  ${v8source}/src/builtins/builtins-interpreter-gen.cc
  ${v8source}/src/builtins/builtins-intl-gen.cc
  ${v8source}/src/builtins/builtins-iterator-gen.cc
  ${v8source}/src/builtins/builtins-lazy-gen.cc
  ${v8source}/src/builtins/builtins-math-gen.cc
  ${v8source}/src/builtins/builtins-microtask-queue-gen.cc
  ${v8source}/src/builtins/builtins-number-gen.cc
  ${v8source}/src/builtins/builtins-object-gen.cc
  ${v8source}/src/builtins/builtins-promise-gen.cc
  ${v8source}/src/builtins/builtins-proxy-gen.cc
  ${v8source}/src/builtins/builtins-reflect-gen.cc
  ${v8source}/src/builtins/builtins-regexp-gen.cc
  ${v8source}/src/builtins/builtins-sharedarraybuffer-gen.cc
  ${v8source}/src/builtins/builtins-string-gen.cc
  ${v8source}/src/builtins/builtins-symbol-gen.cc
  ${v8source}/src/builtins/builtins-typed-array-gen.cc
  ${v8source}/src/builtins/builtins-wasm-gen.cc
  ${v8source}/src/builtins/growable-fixed-array-gen.cc
  ${v8source}/src/builtins/setup-builtins-internal.cc
  ${v8source}/src/codegen/code-stub-assembler.cc
  ${v8source}/src/heap/setup-heap-internal.cc
  ${v8source}/src/ic/accessor-assembler.cc
  ${v8source}/src/ic/binary-op-assembler.cc
  ${v8source}/src/ic/keyed-store-generic.cc
  ${v8source}/src/interpreter/interpreter-assembler.cc
  ${v8source}/src/interpreter/interpreter-generator.cc
  ${v8source}/src/interpreter/interpreter-intrinsics-generator.cc
)

add_definitions(-DV8_USE_EXTERNAL_STARTUP_DATA)
add_definitions(-DV8_ENABLE_REGEXP_INTERPRETER_THREADED_DISPATCH)
add_definitions(-D__STDC_CONSTANT_MACROS)
add_definitions(-DV8_DEPRECATION_WARNINGS)
add_definitions(-DV8_SHARED_RO_HEAP)
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
  set(${PROJECT_NAME}_sources ${${PROJECT_NAME}_sources}
    ${v8source}/src/builtins/x64/builtins-x64.cc
  )
elseif(${ARCHITECTURE} STREQUAL "i386" OR ${ARCHITECTURE} STREQUAL "i486" OR ${ARCHITECTURE} STREQUAL "i586"  OR ${ARCHITECTURE} STREQUAL "i686")
  add_definitions(V8_TARGET_ARCH_IA32)
  set(${PROJECT_NAME}_sources ${${PROJECT_NAME}_sources}
    ${v8source}/src/builtins/ia32/builtins-ia32.cc
  )
endif()

add_library(${PROJECT_NAME}_obj OBJECT ${${PROJECT_NAME}_sources})
add_library(${PROJECT_NAME}_static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}_obj>)
set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

add_library(${PROJECT_NAME}_obj_pic OBJECT ${${PROJECT_NAME}_sources})
set_property(TARGET ${PROJECT_NAME}_obj_pic PROPERTY POSITION_INDEPENDENT_CODE 1)

add_dependencies(${PROJECT_NAME}_obj
  run_torque
)
add_dependencies(${PROJECT_NAME}_obj_pic
  run_torque
)

