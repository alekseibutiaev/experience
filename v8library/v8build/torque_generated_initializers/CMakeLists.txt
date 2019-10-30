project(torque_generated_initializers)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti -Wno-comment -Wno-return-type -Wno-deprecated-declarations")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON}")

add_definitions(-DV8_INTL_SUPPORT)

include_directories(
  ${v8source}
  ${v8source}/include
  ${CMAKE_BINARY_DIR}/v8build/gen/
)

set(${PROJECT_NAME}_gen
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/exported-macros-assembler-tq.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/arguments-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-copywithin-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-every-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-filter-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-findindex-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-find-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-foreach-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-join-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-lastindexof-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-map-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-of-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-reduce-right-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-reduce-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-reverse-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-shift-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-slice-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-some-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-splice-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/array-unshift-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/base-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/bigint-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/boolean-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/collections-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/data-view-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/extras-utils-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/frames-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/growable-fixed-array-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/internal-coverage-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/iterator-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/math-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/object-fromentries-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/object-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/proxy-constructor-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/proxy-delete-property-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/proxy-get-property-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/proxy-get-prototype-of-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/proxy-has-property-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/proxy-is-extensible-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/proxy-prevent-extensions-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/proxy-revocable-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/proxy-revoke-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/proxy-set-property-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/proxy-set-prototype-of-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/proxy-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/reflect-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/regexp-exec-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/regexp-match-all-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/regexp-match-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/regexp-replace-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/regexp-search-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/regexp-source-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/regexp-split-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/regexp-test-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/regexp-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/string-endswith-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/string-html-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/string-iterator-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/string-pad-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/string-repeat-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/string-slice-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/string-startswith-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/string-substring-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/string-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/torque-internal-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/typed-array-createtypedarray-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/typed-array-every-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/typed-array-filter-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/typed-array-findindex-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/typed-array-find-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/typed-array-foreach-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/typed-array-reduceright-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/typed-array-reduce-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/typed-array-slice-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/typed-array-some-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/typed-array-subarray-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/builtins/typed-array-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/src/objects/intl-objects-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/test/torque/test-torque-tq-csa.cc
  ${CMAKE_BINARY_DIR}/v8build/gen/torque-generated/third_party/v8/builtins/array-sort-tq-csa.cc
)

add_compile_options(-fno-strict-aliasing --param=ssp-buffer-size=4 -fstack-protector -funwind-tables)

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

set_source_files_properties(${${PROJECT_NAME}_gen} PROPERTIES GENERATED TRUE)

add_library(${PROJECT_NAME}_obj OBJECT ${${PROJECT_NAME}_gen})

add_library(${PROJECT_NAME}_obj_pic OBJECT ${${PROJECT_NAME}_gen})
set_property(TARGET ${PROJECT_NAME}_obj_pic PROPERTY POSITION_INDEPENDENT_CODE 1)

add_dependencies(${PROJECT_NAME}_obj
  bytecodes-builtins-list
  run_torque
)

add_dependencies(${PROJECT_NAME}_obj_pic
  bytecodes-builtins-list
  run_torque
)

