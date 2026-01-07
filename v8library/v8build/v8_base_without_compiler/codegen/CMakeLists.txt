project(codegen)

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
  ${v8source}/src/codegen/assembler-arch.h
  ${v8source}/src/codegen/assembler-inl.h
  ${v8source}/src/codegen/assembler.h
  ${v8source}/src/codegen/bailout-reason.h
  ${v8source}/src/codegen/callable.h
  ${v8source}/src/codegen/code-comments.h
  ${v8source}/src/codegen/code-desc.h
  ${v8source}/src/codegen/code-factory.h
  ${v8source}/src/codegen/code-reference.h
  ${v8source}/src/codegen/compilation-cache.h
  ${v8source}/src/codegen/compiler.h
  ${v8source}/src/codegen/constant-pool.h
  ${v8source}/src/codegen/constants-arch.h
  ${v8source}/src/codegen/cpu-features.h
  ${v8source}/src/codegen/external-reference-table.h
  ${v8source}/src/codegen/external-reference.h
  ${v8source}/src/codegen/flush-instruction-cache.h
  ${v8source}/src/codegen/handler-table.h
  ${v8source}/src/codegen/interface-descriptors.h
  ${v8source}/src/codegen/label.h
  ${v8source}/src/codegen/machine-type.h
  ${v8source}/src/codegen/macro-assembler-inl.h
  ${v8source}/src/codegen/macro-assembler.h
  ${v8source}/src/codegen/optimized-compilation-info.h
  ${v8source}/src/codegen/pending-optimization-table.h
  ${v8source}/src/codegen/register-arch.h
  ${v8source}/src/codegen/register-configuration.h
  ${v8source}/src/codegen/register.h
  ${v8source}/src/codegen/reglist.h
  ${v8source}/src/codegen/reloc-info.h
  ${v8source}/src/codegen/safepoint-table.h
  ${v8source}/src/codegen/signature.h
  ${v8source}/src/codegen/source-position-table.h
  ${v8source}/src/codegen/source-position.h
  ${v8source}/src/codegen/string-constants.h
  ${v8source}/src/codegen/tick-counter.h
  ${v8source}/src/codegen/tnode.h
  ${v8source}/src/codegen/turbo-assembler.h
  ${v8source}/src/codegen/unoptimized-compilation-info.h
)

set(${PROJECT_NAME}_sources
   ${v8source}/src/codegen/assembler.cc
   ${v8source}/src/codegen/bailout-reason.cc
   ${v8source}/src/codegen/code-comments.cc
   ${v8source}/src/codegen/code-desc.cc
   ${v8source}/src/codegen/code-factory.cc
   ${v8source}/src/codegen/code-reference.cc
   ${v8source}/src/codegen/compilation-cache.cc
   ${v8source}/src/codegen/compiler.cc
   ${v8source}/src/codegen/constant-pool.cc
   ${v8source}/src/codegen/external-reference-table.cc
   ${v8source}/src/codegen/external-reference.cc
   ${v8source}/src/codegen/flush-instruction-cache.cc
   ${v8source}/src/codegen/handler-table.cc
   ${v8source}/src/codegen/interface-descriptors.cc
   ${v8source}/src/codegen/machine-type.cc
   ${v8source}/src/codegen/optimized-compilation-info.cc
   ${v8source}/src/codegen/pending-optimization-table.cc
   ${v8source}/src/codegen/register-configuration.cc
   ${v8source}/src/codegen/register.cc
   ${v8source}/src/codegen/reloc-info.cc
   ${v8source}/src/codegen/safepoint-table.cc
   ${v8source}/src/codegen/source-position-table.cc
   ${v8source}/src/codegen/source-position.cc
   ${v8source}/src/codegen/string-constants.cc
   ${v8source}/src/codegen/tick-counter.cc
   ${v8source}/src/codegen/turbo-assembler.cc
   ${v8source}/src/codegen/unoptimized-compilation-info.cc
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

