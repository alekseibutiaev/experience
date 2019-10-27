project(v8_base_without_compiler)

add_subdirectory(v8_base_without_compiler0)
add_subdirectory(v8_base_without_compiler1)
add_subdirectory(v8_base_without_compiler2)
add_subdirectory(v8_base_without_compiler3)
add_subdirectory(v8_base_without_compiler4)
add_subdirectory(v8_base_without_compiler5)
add_subdirectory(v8_base_without_compiler6)
add_subdirectory(v8_base_without_compiler7)
add_subdirectory(v8_base_without_compiler8)
add_subdirectory(v8_base_without_compiler9)

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
  ${v8source}/src/trap-handler/handler-inside-posix.cc
  ${v8source}/src/trap-handler/handler-outside.cc
  ${v8source}/src/trap-handler/handler-outside-posix.cc
  ${v8source}/src/trap-handler/handler-shared.cc
  ${v8source}/src/utils/address-map.cc
  ${v8source}/src/utils/allocation.cc
  ${v8source}/src/utils/bit-vector.cc
  ${v8source}/src/utils/detachable-vector.cc
  ${v8source}/src/utils/identity-map.cc
  ${v8source}/src/utils/memcopy.cc
  ${v8source}/src/utils/ostreams.cc
  ${v8source}/src/utils/utils.cc
  ${v8source}/src/utils/version.cc
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
  ${v8source}/src/wasm/wasm-module.cc
  ${v8source}/src/wasm/wasm-module-sourcemap.cc
  ${v8source}/src/wasm/wasm-objects.cc
  ${v8source}/src/wasm/wasm-opcodes.cc
  ${v8source}/src/wasm/wasm-result.cc
  ${v8source}/src/wasm/wasm-serialization.cc
  ${v8source}/src/wasm/wasm-text.cc
  ${v8source}/src/zone/accounting-allocator.cc
  ${v8source}/src/zone/zone.cc
  ${v8source}/src/zone/zone-segment.cc
)

set(${PROJECT_NAME}_gen
  ${v8source}/src/Debug/debug.cc
  ${v8source}/src/Debug/debug-coverage.cc
  ${v8source}/src/Debug/debug-evaluate.cc
  ${v8source}/src/Debug/debug-frames.cc
  ${v8source}/src/Debug/debug-property-iterator.cc
  ${v8source}/src/Debug/debug-scope-iterator.cc
  ${v8source}/src/Debug/debug-scopes.cc
  ${v8source}/src/Debug/debug-stack-trace-iterator.cc
  ${v8source}/src/Debug/debug-type-profile.cc
  ${v8source}/src/Debug/liveedit.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/src/regexp/special-case.cc
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

if(${ARCHITECTURE} STREQUAL "x86_64")
  set(${PROJECT_NAME}_sources ${${PROJECT_NAME}_sources}
    ${v8source}/src/codegen/x64/assembler-x64.cc
    ${v8source}/src/codegen/x64/cpu-x64.cc
    ${v8source}/src/codegen/x64/interface-descriptors-x64.cc
    ${v8source}/src/codegen/x64/macro-assembler-x64.cc
    ${v8source}/src/deoptimizer/x64/deoptimizer-x64.cc
    ${v8source}/src/diagnostics/x64/disasm-x64.cc
    ${v8source}/src/diagnostics/x64/eh-frame-x64.cc
    ${v8source}/src/execution/x64/frame-constants-x64.cc
    ${v8source}/src/regexp/x64/regexp-macro-assembler-x64.cc
  )
  set(${PROJECT_NAME}_gen ${${PROJECT_NAME}_gen}
    ${v8source}/src/Debug/x64/debug-x64.cc
  )
elseif(${ARCHITECTURE} STREQUAL "i386" OR ${ARCHITECTURE} STREQUAL "i486" OR ${ARCHITECTURE} STREQUAL "i586"  OR ${ARCHITECTURE} STREQUAL "i686")
  set(${PROJECT_NAME}_sources ${${PROJECT_NAME}_sources}
    ${v8source}/src/builtins/ia32/builtins-ia32.cc
    ${v8source}/src/codegen/ia32/assembler-ia32.cc
    ${v8source}/src/codegen/ia32/cpu-ia32.cc
    ${v8source}/src/codegen/ia32/interface-descriptors-ia32.cc
    ${v8source}/src/codegen/ia32/macro-assembler-ia32.cc
    ${v8source}/src/deoptimizer/ia32/deoptimizer-ia32.cc
    ${v8source}/src/diagnostics/ia32/disasm-ia32.cc
    ${v8source}/src/execution/ia32/frame-constants-ia32.cc
    ${v8source}/src/regexp/ia32/regexp-macro-assembler-ia32.cc
  )
  set(${PROJECT_NAME}_gen ${${PROJECT_NAME}_gen}
    ${v8source}/src/Debug/ia32/debug-ia32.cc
  )
endif()

set_source_files_properties(${${PROJECT_NAME}_gen} PROPERTIES GENERATED TRUE)

add_library(${PROJECT_NAME}_obj OBJECT ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_gen})

add_library(${PROJECT_NAME}_obj_pic OBJECT ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_gen})
set_property(TARGET ${PROJECT_NAME}_obj_pic PROPERTY POSITION_INDEPENDENT_CODE 1)

add_dependencies(${PROJECT_NAME}_obj
  rename_debug
  bytecodes-builtins-list
  tq_files
  gen-regexp-special-case_files
  ${PROJECT_NAME}0_obj
  ${PROJECT_NAME}1_obj
  ${PROJECT_NAME}2_obj
  ${PROJECT_NAME}3_obj
  ${PROJECT_NAME}4_obj
  ${PROJECT_NAME}5_obj
  ${PROJECT_NAME}6_obj
  ${PROJECT_NAME}7_obj
  ${PROJECT_NAME}8_obj
  ${PROJECT_NAME}9_obj
)

add_dependencies(${PROJECT_NAME}_obj_pic
  rename_debug
  bytecodes-builtins-list
  tq_files
  gen-regexp-special-case_files
  ${PROJECT_NAME}0_obj_pic
  ${PROJECT_NAME}1_obj_pic
  ${PROJECT_NAME}2_obj_pic
  ${PROJECT_NAME}3_obj_pic
  ${PROJECT_NAME}4_obj_pic
  ${PROJECT_NAME}5_obj_pic
  ${PROJECT_NAME}6_obj_pic
  ${PROJECT_NAME}7_obj_pic
  ${PROJECT_NAME}8_obj_pic
  ${PROJECT_NAME}9_obj_pic
)

