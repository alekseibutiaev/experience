project(v8_external_snapshot)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON} -O3 -g0")

include_directories(
  ${v8source}
  ${v8source}/include
  ${CMAKE_BINARY_DIR}/v8build/gen
)

set(${PROJECT_NAME}_sources
  ${v8source}/src/snapshot/snapshot-external.cc
  ${v8source}/src/snapshot/natives-external.cc
  ${v8source}/src/init/setup-isolate-deserialize.cc
)

if(OPTION_V8_EMBEDDED_BUILTINS)
  set(${PROJECT_NAME}_gen
    ${CMAKE_BINARY_DIR}/v8build/gen/embedded.S
  )
  set_property(SOURCE ${${PROJECT_NAME}_gen} PROPERTY LANGUAGE C)
  set_source_files_properties(${${PROJECT_NAME}_gen} PROPERTIES GENERATED TRUE)
else(OPTION_V8_EMBEDDED_BUILTINS)
  set(${PROJECT_NAME}_sources ${${PROJECT_NAME}_sources}
    ${v8source}/src/snapshot/embedded/embedded-empty.cc
  )
endif()

add_definitions(-DV8_USE_EXTERNAL_STARTUP_DATA)
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
elseif(${ARCHITECTURE} STREQUAL "i386" OR ${ARCHITECTURE} STREQUAL "i486" OR ${ARCHITECTURE} STREQUAL "i586"  OR ${ARCHITECTURE} STREQUAL "i686")
  add_definitions(V8_TARGET_ARCH_IA32)
endif()

add_library(${PROJECT_NAME}_obj OBJECT ${${PROJECT_NAME}_gen} ${${PROJECT_NAME}_sources})

add_library(${PROJECT_NAME}_obj_pic OBJECT ${${PROJECT_NAME}_gen} ${${PROJECT_NAME}_sources})
set_property(TARGET ${PROJECT_NAME}_obj_pic PROPERTY POSITION_INDEPENDENT_CODE 1)

add_dependencies(${PROJECT_NAME}_obj
  bytecodes-builtins-list
  run_torque
  run_mksnapshot
)

add_dependencies(${PROJECT_NAME}_obj_pic
  bytecodes-builtins-list
  run_torque
  run_mksnapshot
)

if(ENABLE_V8_EMBEDDED_BUILTINS)

  add_dependencies(${PROJECT_NAME}_obj
    run_mksnapshot
  )

  add_dependencies(${PROJECT_NAME}_obj_pic
    run_mksnapshot
  )

endif()

add_custom_target(v8_external_snapshot ALL DEPENDS ${${PROJECT_NAME}_obj} ${${PROJECT_NAME}_obj_pic})

