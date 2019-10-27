project(v8_base_without_compiler)

add_subdirectory(api)
add_subdirectory(arch)
add_subdirectory(asmjs)
add_subdirectory(ast)
add_subdirectory(builtins)
add_subdirectory(codegen)
add_subdirectory(common)
add_subdirectory(date)
add_subdirectory(debug)
add_subdirectory(deoptimizer)
add_subdirectory(execution)
add_subdirectory(extensions)
add_subdirectory(flags)
add_subdirectory(handles)
add_subdirectory(heap)
add_subdirectory(ic)
add_subdirectory(init)
add_subdirectory(interpreter)
add_subdirectory(json)
add_subdirectory(logging)
add_subdirectory(numbers)
add_subdirectory(objects)
add_subdirectory(parsing)
add_subdirectory(profiler)
add_subdirectory(regexp)
add_subdirectory(runtime)
add_subdirectory(sanitizer)
add_subdirectory(snapshot)
add_subdirectory(strings)
add_subdirectory(tasks)
add_subdirectory(third_party)
add_subdirectory(tracing)
add_subdirectory(trap-handler)
add_subdirectory(utils)
add_subdirectory(wasm)
add_subdirectory(zone)

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

if(${OS} STREQUAL "GNU/Linux")

  set(${PROJECT_NAME}_headers
    ${v8source}/src/trap-handler/handler-inside-posix.h
  )

  set(${PROJECT_NAME}_sources
    ${v8source}/src/trap-handler/handler-inside-posix.cc
    ${v8source}/src/trap-handler/handler-outside-posix.cc
  )

endif()

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
elseif(${ARCHITECTURE} STREQUAL "i386" OR ${ARCHITECTURE} STREQUAL "i486" OR ${ARCHITECTURE} STREQUAL "i586"  OR ${ARCHITECTURE} STREQUAL "i686")
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

  api_obj
  asmjs_obj
  ast_obj
  builtins_obj
  codegen_obj
  common_obj
  date_obj
  debug_obj
  deoptimizer_obj
  execution_obj
  extensions_obj
  flags_obj
  handles_obj
  heap_obj
  ic_obj
  init_obj
  interpreter_obj
  logging_obj
  numbers_obj
  objects_obj
  parsing_obj
  profiler_obj
  regexp_obj
  runtime_obj
  sanitizer_obj
  snapshot_obj
  strings_obj
  tasks_obj
  third_party_obj
  tracing_obj
  trap-handler_obj
  utils_obj
  wasm_obj
  zone_obj
  arch_obj
)

add_dependencies(${PROJECT_NAME}_obj_pic
  rename_debug
  bytecodes-builtins-list
  tq_files
  gen-regexp-special-case_files

  api_obj_pic
  asmjs_obj_pic
  ast_obj_pic
  builtins_obj_pic
  codegen_obj_pic
  common_obj_pic
  date_obj_pic
  debug_obj_pic
  deoptimizer_obj_pic
  execution_obj_pic
  extensions_obj_pic
  flags_obj_pic
  handles_obj_pic
  heap_obj_pic
  ic_obj_pic
  init_obj_pic
  interpreter_obj_pic
  logging_obj_pic
  numbers_obj_pic
  objects_obj_pic
  parsing_obj_pic
  profiler_obj_pic
  regexp_obj_pic
  runtime_obj_pic
  sanitizer_obj_pic
  snapshot_obj_pic
  strings_obj_pic
  tasks_obj_pic
  third_party_obj_pic
  tracing_obj_pic
  trap-handler_obj_pic
  utils_obj_pic
  wasm_obj_pic
  zone_obj_pic
  arch_obj_pic
)

