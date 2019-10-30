project(gen-regexp-special-case)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fexceptions -frtti -Wno-return-type -Wno-maybe-uninitialized")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON}")

include_directories(
  ${v8source}
  ${v8source}/include
  ${CMAKE_BINARY_DIR}/v8build
  ${ICU_INCLUDE_DIRS}
)

set(${PROJECT_NAME}_sources
  ${v8source}/src/regexp/gen-regexp-special-case.cc
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

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

target_link_libraries(${PROJECT_NAME}
  v8_libbase_static
  ${ICU_LIBRARIES}
  pthread
)

add_custom_command(
  OUTPUT gen-regexp-special-case_build
  DEPENDS gen-regexp-special-case
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/v8build/gen/src/regexp/
  COMMAND ${PYTHON_EXECUTABLE}
    ${v8source}/tools/run.py
    ${CMAKE_CURRENT_BINARY_DIR}/gen-regexp-special-case
    ${CMAKE_BINARY_DIR}/v8build/gen/src/regexp/special-case.cc
  COMMAND ${CMAKE_COMMAND} -E touch gen-regexp-special-case_build
)

add_custom_target(gen-regexp-special-case_files DEPENDS gen-regexp-special-case_build)

