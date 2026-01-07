project(regexp)

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
  ${v8source}/src/regexp/property-sequences.h
  ${v8source}/src/regexp/regexp-ast.h
  ${v8source}/src/regexp/regexp-bytecode-generator-inl.h
  ${v8source}/src/regexp/regexp-bytecode-generator.h
  ${v8source}/src/regexp/regexp-bytecode-peephole.h
  ${v8source}/src/regexp/regexp-bytecodes.h
  ${v8source}/src/regexp/regexp-compiler.h
  ${v8source}/src/regexp/regexp-dotprinter.h
  ${v8source}/src/regexp/regexp-interpreter.h
  ${v8source}/src/regexp/regexp-macro-assembler-arch.h
  ${v8source}/src/regexp/regexp-macro-assembler-tracer.h
  ${v8source}/src/regexp/regexp-macro-assembler.h
  ${v8source}/src/regexp/regexp-nodes.h
  ${v8source}/src/regexp/regexp-parser.h
  ${v8source}/src/regexp/regexp-stack.h
  ${v8source}/src/regexp/regexp-utils.h
  ${v8source}/src/regexp/regexp.h
  ${v8source}/src/regexp/special-case.h
)
set(${PROJECT_NAME}_sources
  ${v8source}/src/regexp/property-sequences.cc
  ${v8source}/src/regexp/regexp-ast.cc
  ${v8source}/src/regexp/regexp-bytecode-generator.cc
  ${v8source}/src/regexp/regexp-bytecode-peephole.cc
  ${v8source}/src/regexp/regexp-bytecodes.cc
  ${v8source}/src/regexp/regexp-compiler-tonode.cc
  ${v8source}/src/regexp/regexp-compiler.cc
  ${v8source}/src/regexp/regexp-dotprinter.cc
  ${v8source}/src/regexp/regexp-interpreter.cc
  ${v8source}/src/regexp/regexp-macro-assembler-tracer.cc
  ${v8source}/src/regexp/regexp-macro-assembler.cc
  ${v8source}/src/regexp/regexp-parser.cc
  ${v8source}/src/regexp/regexp-stack.cc
  ${v8source}/src/regexp/regexp-utils.cc
  ${v8source}/src/regexp/regexp.cc
)

set(${PROJECT_NAME}_gen
  ${CMAKE_BINARY_DIR}/v8build/gen/src/regexp/special-case.cc
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

set_source_files_properties(${${PROJECT_NAME}_gen} PROPERTIES GENERATED TRUE)

add_library(${PROJECT_NAME}_obj OBJECT ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_gen})

add_library(${PROJECT_NAME}_obj_pic OBJECT ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers} ${${PROJECT_NAME}_gen})
set_property(TARGET ${PROJECT_NAME}_obj_pic PROPERTY POSITION_INDEPENDENT_CODE 1)

add_dependencies(${PROJECT_NAME}_obj
  rename_debug
  bytecodes-builtins-list
  gen-regexp-special-case_files
  run_torque
)

add_dependencies(${PROJECT_NAME}_obj_pic
  rename_debug
  bytecodes-builtins-list
  gen-regexp-special-case_files
  run_torque
)

