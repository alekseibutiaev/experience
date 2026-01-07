project(v8)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON}")

include_directories(
  ${v8source}
  ${v8source}/include
  ${ICU_INCLUDE_DIRS}
)

set(${PROJECT_NAME}_sources
  ${v8source}/src/utils/v8dll-main.cc
)

add_definitions(-DV8_USE_EXTERNAL_STARTUP_DATA)
add_definitions(-DUSING_V8_SHARED)
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
  set(LIB_DESTINATION lib/x86_64-linux-gnu/)
elseif(${ARCHITECTURE} STREQUAL "i386" OR ${ARCHITECTURE} STREQUAL "i486" OR ${ARCHITECTURE} STREQUAL "i586"  OR ${ARCHITECTURE} STREQUAL "i686")
  add_definitions(V8_TARGET_ARCH_IA32)
  set(LIB_DESTINATION lib/i386-linux-gnu/)
endif()

add_library(${PROJECT_NAME}_obj OBJECT ${${PROJECT_NAME}_sources})

add_library(${PROJECT_NAME}_static STATIC
  $<TARGET_OBJECTS:v8_libbase_obj>
  $<TARGET_OBJECTS:v8_libsampler_obj>
  $<TARGET_OBJECTS:v8_compiler_obj>
  $<TARGET_OBJECTS:v8_external_snapshot_obj>
  $<TARGET_OBJECTS:torque_generated_definitions_obj>
  $<TARGET_OBJECTS:inspector_obj>
  $<TARGET_OBJECTS:${PROJECT_NAME}_obj>
)

set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME}_static
  v8_base_without_compiler_static
  encoding_static
  bindings_static
)

add_library(${PROJECT_NAME}_obj_pic OBJECT ${${PROJECT_NAME}_sources})
set_property(TARGET ${PROJECT_NAME}_obj_pic PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(${PROJECT_NAME}_static_pic STATIC
  $<TARGET_OBJECTS:v8_libbase_obj_pic>
  $<TARGET_OBJECTS:v8_libsampler_obj_pic>
  $<TARGET_OBJECTS:v8_compiler_obj_pic>
  $<TARGET_OBJECTS:v8_external_snapshot_obj_pic>
  $<TARGET_OBJECTS:torque_generated_definitions_obj_pic>
  $<TARGET_OBJECTS:inspector_obj_pic>
  $<TARGET_OBJECTS:${PROJECT_NAME}_obj_pic>
)

target_link_libraries(${PROJECT_NAME}_static_pic
  v8_base_without_compiler_static
  encoding_static_pic
  bindings_static_pic
)

add_library(${PROJECT_NAME} SHARED
  $<TARGET_OBJECTS:v8_libbase_obj_pic>
  $<TARGET_OBJECTS:v8_libsampler_obj_pic>
  $<TARGET_OBJECTS:v8_compiler_obj_pic>
  $<TARGET_OBJECTS:v8_external_snapshot_obj_pic>
  $<TARGET_OBJECTS:torque_generated_definitions_obj_pic>
  $<TARGET_OBJECTS:inspector_obj_pic>
  $<TARGET_OBJECTS:${PROJECT_NAME}_obj_pic>
)

target_link_libraries(${PROJECT_NAME}
  v8_base_without_compiler_static_pic
  bindings_static_pic
  encoding_static_pic
)

add_dependencies(${PROJECT_NAME}_obj
  rename_debug
  bytecodes-builtins-list
  run_torque
  run_mksnapshot
)

add_dependencies(${PROJECT_NAME}_obj_pic
  rename_debug
  bytecodes-builtins-list
  run_torque
  run_mksnapshot
)

install(FILES
  ${v8source}/include/v8.h
  ${v8source}/include/v8-platform.h
  ${v8source}/include/v8-wasm-trap-handler-posix.h
  ${v8source}/include/v8-profiler.h
  ${v8source}/include/v8-version-string.h
  ${v8source}/include/v8-testing.h
  ${v8source}/include/v8-internal.h
  ${v8source}/include/v8-version.h
  ${v8source}/include/v8-inspector.h
  ${v8source}/include/v8-wasm-trap-handler-win.h
  ${v8source}/include/v8-util.h
  ${v8source}/include/v8-inspector-protocol.h
  ${v8source}/include/v8.h
  ${v8source}/include/v8config.h
  ${v8source}/include/v8-value-serializer-version.h
  DESTINATION include/v8
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/libv8.so
  ${CMAKE_CURRENT_BINARY_DIR}/libv8.a
  ${CMAKE_CURRENT_BINARY_DIR}/libv8_static_pic.a
  DESTINATION ${LIB_DESTINATION}v8/
)

