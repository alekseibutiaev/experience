project(bindings)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON}")

include_directories(
  ${v8source}
  ${v8source}/include
  ${CMAKE_BINARY_DIR}/v8build
  ${ICU_INCLUDE_DIRS}
)

set(${PROJECT_NAME}_sources
  ${v8source}/third_party/inspector_protocol/bindings/bindings.cc
)

add_definitions(-DNVALGRIND)
add_definitions(-D__STDC_CONSTANT_MACROS)
add_definitions(-D__STDC_FORMAT_MACROS)
add_definitions(-D_GNU_SOURCE)

add_library(${PROJECT_NAME}_obj OBJECT ${${PROJECT_NAME}_sources})
add_library(${PROJECT_NAME}_static STATIC $<TARGET_OBJECTS:${PROJECT_NAME}_obj>)
set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

add_library(${PROJECT_NAME}_obj_pic OBJECT ${${PROJECT_NAME}_sources})
set_property(TARGET ${PROJECT_NAME}_obj_pic PROPERTY POSITION_INDEPENDENT_CODE 1)
add_library(${PROJECT_NAME}_static_pic STATIC $<TARGET_OBJECTS:${PROJECT_NAME}_obj_pic>)

add_dependencies(${PROJECT_NAME}_obj
  bytecodes-builtins-list
)

add_dependencies(${PROJECT_NAME}_obj_pic
  bytecodes-builtins-list
)

