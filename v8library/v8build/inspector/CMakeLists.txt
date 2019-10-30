project(inspector)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti -Wno-return-type -Wno-comment -Wno-deprecated-declarations")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON}")

include_directories(
  /
  ${v8source}
  ${v8source}/include/
  ${v8source}/src
  ${CMAKE_BINARY_DIR}/v8build
  ${CMAKE_BINARY_DIR}/v8build/gen
  ${ICU_INCLUDE_DIRS}
)

add_custom_command(
  OUTPUT inspector_generated_file
  COMMAND ${PYTHON_EXECUTABLE} ${v8source}/third_party/inspector_protocol/code_generator.py
    --jinja_dir ${v8source}/third_party
    --config ${v8source}/src/inspector/inspector_protocol_config.json
    --output_base ${v8source}/src/inspector
    --inspector_protocol_dir /third_party/inspector_protocol/
  COMMAND ${CMAKE_COMMAND} -E touch inspector_generated_file
)

add_custom_target(inspector_generated DEPENDS inspector_generated_file)

set(${PROJECT_NAME}_gen
  ${v8source}/src/inspector/protocol/Console.cpp
  ${v8source}/src/inspector/protocol/Debugger.cpp
  ${v8source}/src/inspector/protocol/HeapProfiler.cpp
  ${v8source}/src/inspector/protocol/Profiler.cpp
  ${v8source}/src/inspector/protocol/Protocol.cpp
  ${v8source}/src/inspector/protocol/Runtime.cpp
  ${v8source}/src/inspector/protocol/Schema.cpp
)

set(${PROJECT_NAME}_sources
  ${v8source}/src/inspector/custom-preview.cc
  ${v8source}/src/inspector/injected-script.cc
  ${v8source}/src/inspector/inspected-context.cc
  ${v8source}/src/inspector/remote-object-id.cc
  ${v8source}/src/inspector/search-util.cc
  ${v8source}/src/inspector/string-16.cc
  ${v8source}/src/inspector/string-util.cc
  ${v8source}/src/inspector/test-interface.cc
  ${v8source}/src/inspector/v8-console-agent-impl.cc
  ${v8source}/src/inspector/v8-console.cc
  ${v8source}/src/inspector/v8-console-message.cc
  ${v8source}/src/inspector/v8-debugger-agent-impl.cc
  ${v8source}/src/inspector/v8-debugger.cc
  ${v8source}/src/inspector/v8-debugger-script.cc
  ${v8source}/src/inspector/v8-heap-profiler-agent-impl.cc
  ${v8source}/src/inspector/v8-inspector-impl.cc
  ${v8source}/src/inspector/v8-inspector-protocol-encoding.cc
  ${v8source}/src/inspector/v8-inspector-session-impl.cc
  ${v8source}/src/inspector/v8-profiler-agent-impl.cc
  ${v8source}/src/inspector/v8-regex.cc
  ${v8source}/src/inspector/v8-runtime-agent-impl.cc
  ${v8source}/src/inspector/v8-schema-agent-impl.cc
  ${v8source}/src/inspector/v8-stack-trace-impl.cc
  ${v8source}/src/inspector/v8-value-utils.cc
  ${v8source}/src/inspector/v8-string-conversions.cc
  ${v8source}/src/inspector/value-mirror.cc
  ${v8source}/src/inspector/wasm-translation.cc
)

set_source_files_properties(${${PROJECT_NAME}_gen} PROPERTIES GENERATED TRUE)

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

add_library(${PROJECT_NAME}_obj OBJECT ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_gen})
add_library(${PROJECT_NAME}_static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}_obj>)
set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

add_library(${PROJECT_NAME}_obj_pic OBJECT ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_gen})
set_property(TARGET ${PROJECT_NAME}_obj_pic PROPERTY POSITION_INDEPENDENT_CODE 1)

add_dependencies(${PROJECT_NAME}_obj
  bytecodes-builtins-list
  rename_debug
  inspector_generated
)

add_dependencies(${PROJECT_NAME}_obj_pic
  bytecodes-builtins-list
  rename_debug
  inspector_generated
)

