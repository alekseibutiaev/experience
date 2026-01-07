project(arch)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti -Wno-return-type\
    -Wno-comment -Wno-unused-function -Wno-strict-aliasing  -Wno-maybe-uninitialized")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON} -O3 -g0")

include_directories(
  ${v8source}
  ${v8source}/include/
  ${v8source}/src
  ${CMAKE_BINARY_DIR}/v8build
  ${CMAKE_BINARY_DIR}/v8build/gen
  ${ICU_INCLUDE_DIRS}
)

if(${ARCHITECTURE} STREQUAL "x86_64")
    set(${PROJECT_NAME}_headers
      ${v8source}/src/codegen/x64/assembler-x64-inl.h
      ${v8source}/src/codegen/x64/assembler-x64.h
      ${v8source}/src/codegen/x64/constants-x64.h
      ${v8source}/src/codegen/x64/macro-assembler-x64.h
      ${v8source}/src/codegen/x64/register-x64.h
      ${v8source}/src/codegen/x64/sse-instr.h
      ${v8source}/src/execution/x64/frame-constants-x64.h
      ${v8source}/src/regexp/x64/regexp-macro-assembler-x64.h
      ${v8source}/src/wasm/baseline/x64/liftoff-assembler-x64.h
    )
    set(${PROJECT_NAME}_sources
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

elseif(${ARCHITECTURE} STREQUAL "i386" OR ${ARCHITECTURE} STREQUAL "i486" OR ${ARCHITECTURE} STREQUAL "i586"  OR ${ARCHITECTURE} STREQUAL "i686")
    set(${PROJECT_NAME}_headers
      ${v8source}/src/codegen/ia32/assembler-ia32-inl.h
      ${v8source}/src/codegen/ia32/assembler-ia32.h
      ${v8source}/src/codegen/ia32/constants-ia32.h
      ${v8source}/src/codegen/ia32/macro-assembler-ia32.h
      ${v8source}/src/codegen/ia32/register-ia32.h
      ${v8source}/src/codegen/ia32/sse-instr.h
      ${v8source}/src/execution/ia32/frame-constants-ia32.h
      ${v8source}/src/regexp/ia32/regexp-macro-assembler-ia32.h
      ${v8source}/src/wasm/baseline/ia32/liftoff-assembler-ia32.h
    )
    set(${PROJECT_NAME}_sources
      ${v8source}/src/codegen/ia32/assembler-ia32.cc
      ${v8source}/src/codegen/ia32/cpu-ia32.cc
      ${v8source}/src/codegen/ia32/interface-descriptors-ia32.cc
      ${v8source}/src/codegen/ia32/macro-assembler-ia32.cc
      ${v8source}/src/deoptimizer/ia32/deoptimizer-ia32.cc
      ${v8source}/src/diagnostics/ia32/disasm-ia32.cc
      ${v8source}/src/execution/ia32/frame-constants-ia32.cc
      ${v8source}/src/regexp/ia32/regexp-macro-assembler-ia32.cc
    )
endif()


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


