project(wasm)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti -Wno-return-type\
    -Wno-comment -Wno-unused-function -Wno-strict-aliasing  -Wno-maybe-uninitialized")

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
  ${v8source}/src/wasm/baseline/liftoff-assembler-defs.h
  ${v8source}/src/wasm/baseline/liftoff-assembler.h
  ${v8source}/src/wasm/baseline/liftoff-compiler.h
  ${v8source}/src/wasm/baseline/liftoff-register.h
  ${v8source}/src/wasm/compilation-environment.h
  ${v8source}/src/wasm/decoder.h
  ${v8source}/src/wasm/function-body-decoder-impl.h
  ${v8source}/src/wasm/function-body-decoder.h
  ${v8source}/src/wasm/function-compiler.h
  ${v8source}/src/wasm/graph-builder-interface.h
  ${v8source}/src/wasm/jump-table-assembler.h
  ${v8source}/src/wasm/leb-helper.h
  ${v8source}/src/wasm/local-decl-encoder.h
  ${v8source}/src/wasm/memory-tracing.h
  ${v8source}/src/wasm/module-compiler.h
  ${v8source}/src/wasm/module-decoder.h
  ${v8source}/src/wasm/module-instantiate.h
  ${v8source}/src/wasm/object-access.h
  ${v8source}/src/wasm/signature-map.h
  ${v8source}/src/wasm/streaming-decoder.h
  ${v8source}/src/wasm/value-type.h
  ${v8source}/src/wasm/wasm-arguments.h
  ${v8source}/src/wasm/wasm-code-manager.h
  ${v8source}/src/wasm/wasm-constants.h
  ${v8source}/src/wasm/wasm-engine.h
  ${v8source}/src/wasm/wasm-external-refs.h
  ${v8source}/src/wasm/wasm-feature-flags.h
  ${v8source}/src/wasm/wasm-features.h
  ${v8source}/src/wasm/wasm-import-wrapper-cache.h
  ${v8source}/src/wasm/wasm-interpreter.h
  ${v8source}/src/wasm/wasm-js.h
  ${v8source}/src/wasm/wasm-limits.h
  ${v8source}/src/wasm/wasm-linkage.h
  ${v8source}/src/wasm/wasm-module-builder.h
  ${v8source}/src/wasm/wasm-module-sourcemap.h
  ${v8source}/src/wasm/wasm-module.h
  ${v8source}/src/wasm/wasm-objects-inl.h
  ${v8source}/src/wasm/wasm-objects.h
  ${v8source}/src/wasm/wasm-opcodes.h
  ${v8source}/src/wasm/wasm-result.h
  ${v8source}/src/wasm/wasm-serialization.h
  ${v8source}/src/wasm/wasm-text.h
  ${v8source}/src/wasm/wasm-tier.h
  ${v8source}/src/wasm/wasm-value.h
)

set(${PROJECT_NAME}_sources
  ${v8source}/src/wasm/baseline/liftoff-assembler.cc
  ${v8source}/src/wasm/baseline/liftoff-compiler.cc
  ${v8source}/src/wasm/function-body-decoder.cc
  ${v8source}/src/wasm/function-compiler.cc
  ${v8source}/src/wasm/graph-builder-interface.cc
  ${v8source}/src/wasm/jump-table-assembler.cc
  ${v8source}/src/wasm/local-decl-encoder.cc
  ${v8source}/src/wasm/memory-tracing.cc
  ${v8source}/src/wasm/module-compiler.cc
  ${v8source}/src/wasm/module-decoder.cc
  ${v8source}/src/wasm/module-instantiate.cc
  ${v8source}/src/wasm/signature-map.cc
  ${v8source}/src/wasm/streaming-decoder.cc
  ${v8source}/src/wasm/wasm-code-manager.cc
  ${v8source}/src/wasm/wasm-debug.cc
  ${v8source}/src/wasm/wasm-engine.cc
  ${v8source}/src/wasm/wasm-external-refs.cc
  ${v8source}/src/wasm/wasm-features.cc
  ${v8source}/src/wasm/wasm-import-wrapper-cache.cc
  ${v8source}/src/wasm/wasm-interpreter.cc
  ${v8source}/src/wasm/wasm-js.cc
  ${v8source}/src/wasm/wasm-module-builder.cc
  ${v8source}/src/wasm/wasm-module-sourcemap.cc
  ${v8source}/src/wasm/wasm-module.cc
  ${v8source}/src/wasm/wasm-objects.cc
  ${v8source}/src/wasm/wasm-opcodes.cc
  ${v8source}/src/wasm/wasm-result.cc
  ${v8source}/src/wasm/wasm-serialization.cc
  ${v8source}/src/wasm/wasm-text.cc
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

