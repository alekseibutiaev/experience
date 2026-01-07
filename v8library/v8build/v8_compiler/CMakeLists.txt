project(v8_compiler)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti -Wno-return-type\
    -Wno-comment -Wno-maybe-uninitialized")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON}")

include_directories(
  ${v8source}
  ${v8source}/include/
  ${v8source}/src
  ${CMAKE_BINARY_DIR}/v8build
  ${CMAKE_BINARY_DIR}/v8build/gen
)

set(${PROJECT_NAME}_sources
  ${v8source}/src/compiler/access-builder.cc
  ${v8source}/src/compiler/access-info.cc
  ${v8source}/src/compiler/add-type-assertions-reducer.cc
  ${v8source}/src/compiler/all-nodes.cc
  ${v8source}/src/compiler/backend/code-generator.cc
  ${v8source}/src/compiler/backend/frame-elider.cc
  ${v8source}/src/compiler/backend/gap-resolver.cc
  ${v8source}/src/compiler/backend/instruction.cc
  ${v8source}/src/compiler/backend/instruction-scheduler.cc
  ${v8source}/src/compiler/backend/instruction-selector.cc
  ${v8source}/src/compiler/backend/jump-threading.cc
  ${v8source}/src/compiler/backend/live-range-separator.cc
  ${v8source}/src/compiler/backend/move-optimizer.cc
  ${v8source}/src/compiler/backend/register-allocator.cc
  ${v8source}/src/compiler/backend/register-allocator-verifier.cc
  ${v8source}/src/compiler/basic-block-instrumentor.cc
  ${v8source}/src/compiler/branch-elimination.cc
  ${v8source}/src/compiler/bytecode-analysis.cc
  ${v8source}/src/compiler/bytecode-graph-builder.cc
  ${v8source}/src/compiler/bytecode-liveness-map.cc
  ${v8source}/src/compiler/checkpoint-elimination.cc
  ${v8source}/src/compiler/c-linkage.cc
  ${v8source}/src/compiler/code-assembler.cc
  ${v8source}/src/compiler/common-node-cache.cc
  ${v8source}/src/compiler/common-operator.cc
  ${v8source}/src/compiler/common-operator-reducer.cc
  ${v8source}/src/compiler/compilation-dependencies.cc
  ${v8source}/src/compiler/compiler-source-position-table.cc
  ${v8source}/src/compiler/constant-folding-reducer.cc
  ${v8source}/src/compiler/control-equivalence.cc
  ${v8source}/src/compiler/control-flow-optimizer.cc
  ${v8source}/src/compiler/csa-load-elimination.cc
  ${v8source}/src/compiler/dead-code-elimination.cc
  ${v8source}/src/compiler/decompression-elimination.cc
  ${v8source}/src/compiler/effect-control-linearizer.cc
  ${v8source}/src/compiler/escape-analysis.cc
  ${v8source}/src/compiler/escape-analysis-reducer.cc
  ${v8source}/src/compiler/feedback-source.cc
  ${v8source}/src/compiler/frame.cc
  ${v8source}/src/compiler/frame-states.cc
  ${v8source}/src/compiler/graph-assembler.cc
  ${v8source}/src/compiler/graph.cc
  ${v8source}/src/compiler/graph-reducer.cc
  ${v8source}/src/compiler/graph-trimmer.cc
  ${v8source}/src/compiler/graph-visualizer.cc
  ${v8source}/src/compiler/int64-lowering.cc
  ${v8source}/src/compiler/js-call-reducer.cc
  ${v8source}/src/compiler/js-context-specialization.cc
  ${v8source}/src/compiler/js-create-lowering.cc
  ${v8source}/src/compiler/js-generic-lowering.cc
  ${v8source}/src/compiler/js-graph.cc
  ${v8source}/src/compiler/js-heap-broker.cc
  ${v8source}/src/compiler/js-heap-copy-reducer.cc
  ${v8source}/src/compiler/js-inlining.cc
  ${v8source}/src/compiler/js-inlining-heuristic.cc
  ${v8source}/src/compiler/js-intrinsic-lowering.cc
  ${v8source}/src/compiler/js-native-context-specialization.cc
  ${v8source}/src/compiler/js-operator.cc
  ${v8source}/src/compiler/js-typed-lowering.cc
  ${v8source}/src/compiler/js-type-hint-lowering.cc
  ${v8source}/src/compiler/linkage.cc
  ${v8source}/src/compiler/load-elimination.cc
  ${v8source}/src/compiler/loop-analysis.cc
  ${v8source}/src/compiler/loop-peeling.cc
  ${v8source}/src/compiler/loop-variable-optimizer.cc
  ${v8source}/src/compiler/machine-graph.cc
  ${v8source}/src/compiler/machine-graph-verifier.cc
  ${v8source}/src/compiler/machine-operator.cc
  ${v8source}/src/compiler/machine-operator-reducer.cc
  ${v8source}/src/compiler/map-inference.cc
  ${v8source}/src/compiler/memory-lowering.cc
  ${v8source}/src/compiler/memory-optimizer.cc
  ${v8source}/src/compiler/node-cache.cc
  ${v8source}/src/compiler/node.cc
  ${v8source}/src/compiler/node-marker.cc
  ${v8source}/src/compiler/node-matchers.cc
  ${v8source}/src/compiler/node-origin-table.cc
  ${v8source}/src/compiler/node-properties.cc
  ${v8source}/src/compiler/opcodes.cc
  ${v8source}/src/compiler/operation-typer.cc
  ${v8source}/src/compiler/operator.cc
  ${v8source}/src/compiler/operator-properties.cc
  ${v8source}/src/compiler/osr.cc
  ${v8source}/src/compiler/pipeline.cc
  ${v8source}/src/compiler/pipeline-statistics.cc
  ${v8source}/src/compiler/property-access-builder.cc
  ${v8source}/src/compiler/raw-machine-assembler.cc
  ${v8source}/src/compiler/redundancy-elimination.cc
  ${v8source}/src/compiler/refs-map.cc
  ${v8source}/src/compiler/representation-change.cc
  ${v8source}/src/compiler/schedule.cc
  ${v8source}/src/compiler/scheduler.cc
  ${v8source}/src/compiler/select-lowering.cc
  ${v8source}/src/compiler/serializer-for-background-compilation.cc
  ${v8source}/src/compiler/simd-scalar-lowering.cc
  ${v8source}/src/compiler/simplified-lowering.cc
  ${v8source}/src/compiler/simplified-operator.cc
  ${v8source}/src/compiler/simplified-operator-reducer.cc
  ${v8source}/src/compiler/state-values-utils.cc
  ${v8source}/src/compiler/store-store-elimination.cc
  ${v8source}/src/compiler/type-cache.cc
  ${v8source}/src/compiler/typed-optimization.cc
  ${v8source}/src/compiler/type-narrowing-reducer.cc
  ${v8source}/src/compiler/typer.cc
  ${v8source}/src/compiler/types.cc
  ${v8source}/src/compiler/value-numbering-reducer.cc
  ${v8source}/src/compiler/verifier.cc
  ${v8source}/src/compiler/wasm-compiler.cc
  ${v8source}/src/compiler/zone-stats.cc
)

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

if(${ARCHITECTURE} STREQUAL "x86_64")
  set(${PROJECT_NAME}_sources ${${PROJECT_NAME}_sources}
    ${v8source}/src/compiler/backend/x64/code-generator-x64.cc
    ${v8source}/src/compiler/backend/x64/instruction-scheduler-x64.cc
    ${v8source}/src/compiler/backend/x64/instruction-selector-x64.cc
    ${v8source}/src/compiler/backend/x64/unwinding-info-writer-x64.cc
  )
elseif(${ARCHITECTURE} STREQUAL "i386" OR ${ARCHITECTURE} STREQUAL "i486" OR ${ARCHITECTURE} STREQUAL "i586"  OR ${ARCHITECTURE} STREQUAL "i686")
  set(${PROJECT_NAME}_sources ${${PROJECT_NAME}_sources}
    ${v8source}/src/compiler/backend/ia32/code-generator-ia32.cc
    ${v8source}/src/compiler/backend/ia32/instruction-scheduler-ia32.cc
    ${v8source}/src/compiler/backend/ia32/instruction-selector-ia32.cc
  )
endif()

add_library(${PROJECT_NAME}_obj OBJECT ${${PROJECT_NAME}_sources})

add_library(${PROJECT_NAME}_obj_pic OBJECT ${${PROJECT_NAME}_sources})
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

