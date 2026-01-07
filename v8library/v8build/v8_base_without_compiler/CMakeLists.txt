project(v8_base_without_compiler)

add_subdirectory(api)
add_subdirectory(arch)
add_subdirectory(asmjs)
add_subdirectory(ast)
add_subdirectory(builtins)
add_subdirectory(codegen)
add_subdirectory(common)
add_subdirectory(compiler-dispatcher)
add_subdirectory(date)
add_subdirectory(debug)
add_subdirectory(deoptimizer)
add_subdirectory(diagnostics)
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
add_subdirectory(roots)
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

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti -Wno-return-type\
    -Wno-comment -Wno-unused-function -Wno-maybe-uninitialized")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON} ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON} ")

include_directories(
  ${v8source}
  ${v8source}/include/
  ${v8source}/src
  ${ICU_INCLUDE_DIRS}
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

if(${OS} STREQUAL "GNU/Linux")

  set(${PROJECT_NAME}_headers
    ${v8source}/src/trap-handler/handler-inside-posix.h
  )

  set(${PROJECT_NAME}_sources
    ${v8source}/src/trap-handler/handler-inside-posix.cc
    ${v8source}/src/trap-handler/handler-outside-posix.cc
  )

endif()

if(${ARCHITECTURE} STREQUAL "x86_64")
  add_definitions(-DV8_TARGET_ARCH_X64)
elseif(${ARCHITECTURE} STREQUAL "i386" OR ${ARCHITECTURE} STREQUAL "i486" OR ${ARCHITECTURE} STREQUAL "i586"  OR ${ARCHITECTURE} STREQUAL "i686")
  add_definitions(V8_TARGET_ARCH_IA32)
endif()

add_library(${PROJECT_NAME}_static STATIC
  $<TARGET_OBJECTS:api_obj>
  $<TARGET_OBJECTS:arch_obj>
  $<TARGET_OBJECTS:asmjs_obj>
  $<TARGET_OBJECTS:ast_obj>
  $<TARGET_OBJECTS:builtins_obj>
  $<TARGET_OBJECTS:codegen_obj>
  $<TARGET_OBJECTS:common_obj>
  $<TARGET_OBJECTS:compiler-dispatcher_obj>
  $<TARGET_OBJECTS:date_obj>
  $<TARGET_OBJECTS:debug_obj>
  $<TARGET_OBJECTS:deoptimizer_obj>
  $<TARGET_OBJECTS:diagnostics_obj>
  $<TARGET_OBJECTS:execution_obj>
  $<TARGET_OBJECTS:extensions_obj>
  $<TARGET_OBJECTS:flags_obj>
  $<TARGET_OBJECTS:handles_obj>
  $<TARGET_OBJECTS:heap_obj>
  $<TARGET_OBJECTS:ic_obj>
  $<TARGET_OBJECTS:init_obj>
  $<TARGET_OBJECTS:interpreter_obj>
  $<TARGET_OBJECTS:json_obj>
  $<TARGET_OBJECTS:logging_obj>
  $<TARGET_OBJECTS:numbers_obj>
  $<TARGET_OBJECTS:objects_obj>
  $<TARGET_OBJECTS:parsing_obj>
  $<TARGET_OBJECTS:profiler_obj>
  $<TARGET_OBJECTS:regexp_obj>
  $<TARGET_OBJECTS:roots_obj>
  $<TARGET_OBJECTS:runtime_obj>
  $<TARGET_OBJECTS:sanitizer_obj>
  $<TARGET_OBJECTS:snapshot_obj>
  $<TARGET_OBJECTS:strings_obj>
  $<TARGET_OBJECTS:tasks_obj>
  $<TARGET_OBJECTS:third_party_obj>
  $<TARGET_OBJECTS:tracing_obj>
  $<TARGET_OBJECTS:trap-handler_obj>
  $<TARGET_OBJECTS:utils_obj>
  $<TARGET_OBJECTS:wasm_obj>
  $<TARGET_OBJECTS:zone_obj>
  ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers}
)

add_library(${PROJECT_NAME}_static_pic STATIC
  $<TARGET_OBJECTS:api_obj_pic>
  $<TARGET_OBJECTS:arch_obj_pic>
  $<TARGET_OBJECTS:asmjs_obj_pic>
  $<TARGET_OBJECTS:ast_obj_pic>
  $<TARGET_OBJECTS:builtins_obj_pic>
  $<TARGET_OBJECTS:codegen_obj_pic>
  $<TARGET_OBJECTS:common_obj_pic>
  $<TARGET_OBJECTS:compiler-dispatcher_obj_pic>
  $<TARGET_OBJECTS:date_obj_pic>
  $<TARGET_OBJECTS:debug_obj_pic>
  $<TARGET_OBJECTS:deoptimizer_obj_pic>
  $<TARGET_OBJECTS:diagnostics_obj_pic>
  $<TARGET_OBJECTS:execution_obj_pic>
  $<TARGET_OBJECTS:extensions_obj_pic>
  $<TARGET_OBJECTS:flags_obj_pic>
  $<TARGET_OBJECTS:handles_obj_pic>
  $<TARGET_OBJECTS:heap_obj_pic>
  $<TARGET_OBJECTS:ic_obj_pic>
  $<TARGET_OBJECTS:init_obj_pic>
  $<TARGET_OBJECTS:interpreter_obj_pic>
  $<TARGET_OBJECTS:json_obj_pic>
  $<TARGET_OBJECTS:logging_obj_pic>
  $<TARGET_OBJECTS:numbers_obj_pic>
  $<TARGET_OBJECTS:objects_obj_pic>
  $<TARGET_OBJECTS:parsing_obj_pic>
  $<TARGET_OBJECTS:profiler_obj_pic>
  $<TARGET_OBJECTS:regexp_obj_pic>
  $<TARGET_OBJECTS:roots_obj_pic>
  $<TARGET_OBJECTS:runtime_obj_pic>
  $<TARGET_OBJECTS:sanitizer_obj_pic>
  $<TARGET_OBJECTS:snapshot_obj_pic>
  $<TARGET_OBJECTS:strings_obj_pic>
  $<TARGET_OBJECTS:tasks_obj_pic>
  $<TARGET_OBJECTS:third_party_obj_pic>
  $<TARGET_OBJECTS:tracing_obj_pic>
  $<TARGET_OBJECTS:trap-handler_obj_pic>
  $<TARGET_OBJECTS:utils_obj_pic>
  $<TARGET_OBJECTS:wasm_obj_pic>
  $<TARGET_OBJECTS:zone_obj_pic>
  ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers}
)

set_property(TARGET ${PROJECT_NAME}_static_pic PROPERTY POSITION_INDEPENDENT_CODE 1)

add_dependencies(${PROJECT_NAME}_static
  rename_debug
  bytecodes-builtins-list
  run_torque
)

add_dependencies(${PROJECT_NAME}_static_pic
  rename_debug
  bytecodes-builtins-list
  run_torque
)

