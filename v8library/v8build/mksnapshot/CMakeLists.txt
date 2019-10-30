project(mksnapshot)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fexceptions -frtti -Wno-comment")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON} ")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON} ")

include_directories(
  ${v8source}
  ${v8source}/include/
  ${CMAKE_BINARY_DIR}/v8build/gen
  ${ICU_INCLUDE_DIRS}
)

set(${PROJECT_NAME}_sources
  ${v8source}/src/snapshot/embedded/embedded-file-writer.cc
  ${v8source}/src/snapshot/embedded/platform-embedded-file-writer-aix.cc
  ${v8source}/src/snapshot/embedded/platform-embedded-file-writer-base.cc
  ${v8source}/src/snapshot/embedded/platform-embedded-file-writer-generic.cc
  ${v8source}/src/snapshot/embedded/platform-embedded-file-writer-mac.cc
  ${v8source}/src/snapshot/embedded/platform-embedded-file-writer-win.cc
  ${v8source}/src/snapshot/mksnapshot.cc
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
add_definitions(-DUSING_V8_PLATFORM_SHARED)
add_definitions(-DENABLE_DISASSEMBLER)

if(${ARCHITECTURE} STREQUAL "x86_64")
  add_definitions(-DV8_TARGET_ARCH_X64)
elseif(${ARCHITECTURE} STREQUAL "i386" OR ${ARCHITECTURE} STREQUAL "i486" OR ${ARCHITECTURE} STREQUAL "i586"  OR ${ARCHITECTURE} STREQUAL "i686")
  add_definitions(V8_TARGET_ARCH_IA32)
endif()

add_executable(${PROJECT_NAME}
  $<TARGET_OBJECTS:inspector_obj>
  $<TARGET_OBJECTS:v8_libbase_obj>
  $<TARGET_OBJECTS:v8_compiler_obj>
  $<TARGET_OBJECTS:v8_libsampler_obj>
  $<TARGET_OBJECTS:v8_libplatform_obj>
  $<TARGET_OBJECTS:v8_initializers_obj>
  $<TARGET_OBJECTS:v8_init_obj>
  $<TARGET_OBJECTS:v8_nosnapshot_obj>
  $<TARGET_OBJECTS:torque_generated_definitions_obj>
  $<TARGET_OBJECTS:torque_generated_initializers_obj>
  ${${PROJECT_NAME}_sources}
)

target_link_libraries(${PROJECT_NAME}
  v8_base_without_compiler_static
  encoding_static
  bindings_static
  ${ICU_LIBRARIES}
  pthread
)

add_dependencies(${PROJECT_NAME}
  bytecodes-builtins-list
  run_torque
)

