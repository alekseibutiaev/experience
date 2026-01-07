project(interpreter)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti -Wno-return-type\
    -Wno-comment -Wno-unused-function -Wno-strict-aliasing -Wno-maybe-uninitialized")

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
  ${v8source}/src/interpreter/interpreter-assembler.h
  ${v8source}/src/interpreter/interpreter-generator.h
  ${v8source}/src/interpreter/interpreter-intrinsics-generator.h
  ${v8source}/src/interpreter/block-coverage-builder.h
  ${v8source}/src/interpreter/bytecode-array-accessor.h
  ${v8source}/src/interpreter/bytecode-array-builder.h
  ${v8source}/src/interpreter/bytecode-array-iterator.h
  ${v8source}/src/interpreter/bytecode-array-random-iterator.h
  ${v8source}/src/interpreter/bytecode-array-writer.h
  ${v8source}/src/interpreter/bytecode-decoder.h
  ${v8source}/src/interpreter/bytecode-flags.h
  ${v8source}/src/interpreter/bytecode-generator.h
  ${v8source}/src/interpreter/bytecode-jump-table.h
  ${v8source}/src/interpreter/bytecode-label.h
  ${v8source}/src/interpreter/bytecode-node.h
  ${v8source}/src/interpreter/bytecode-operands.h
  ${v8source}/src/interpreter/bytecode-register-allocator.h
  ${v8source}/src/interpreter/bytecode-register-optimizer.h
  ${v8source}/src/interpreter/bytecode-register.h
  ${v8source}/src/interpreter/bytecode-source-info.h
  ${v8source}/src/interpreter/bytecode-traits.h
  ${v8source}/src/interpreter/bytecodes.h
  ${v8source}/src/interpreter/constant-array-builder.h
  ${v8source}/src/interpreter/control-flow-builders.h
  ${v8source}/src/interpreter/handler-table-builder.h
  ${v8source}/src/interpreter/interpreter-generator.h
  ${v8source}/src/interpreter/interpreter-intrinsics.h
  ${v8source}/src/interpreter/interpreter.h
  ${v8source}/src/interpreter/bytecode-operands.h
  ${v8source}/src/interpreter/bytecodes.h
)

set(${PROJECT_NAME}_sources
  ${v8source}/src/interpreter/interpreter-assembler.cc
  ${v8source}/src/interpreter/interpreter-generator.cc
  ${v8source}/src/interpreter/interpreter-intrinsics-generator.cc
  ${v8source}/src/interpreter/bytecode-array-accessor.cc
  ${v8source}/src/interpreter/bytecode-array-builder.cc
  ${v8source}/src/interpreter/bytecode-array-iterator.cc
  ${v8source}/src/interpreter/bytecode-array-random-iterator.cc
  ${v8source}/src/interpreter/bytecode-array-writer.cc
  ${v8source}/src/interpreter/bytecode-decoder.cc
  ${v8source}/src/interpreter/bytecode-flags.cc
  ${v8source}/src/interpreter/bytecode-generator.cc
  ${v8source}/src/interpreter/bytecode-label.cc
  ${v8source}/src/interpreter/bytecode-node.cc
  ${v8source}/src/interpreter/bytecode-operands.cc
  ${v8source}/src/interpreter/bytecode-register-optimizer.cc
  ${v8source}/src/interpreter/bytecode-register.cc
  ${v8source}/src/interpreter/bytecode-source-info.cc
  ${v8source}/src/interpreter/bytecodes.cc
  ${v8source}/src/interpreter/constant-array-builder.cc
  ${v8source}/src/interpreter/control-flow-builders.cc
  ${v8source}/src/interpreter/handler-table-builder.cc
  ${v8source}/src/interpreter/interpreter-intrinsics.cc
  ${v8source}/src/interpreter/interpreter.cc
  ${v8source}/src/interpreter/bytecode-operands.cc
  ${v8source}/src/interpreter/bytecodes.cc
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

