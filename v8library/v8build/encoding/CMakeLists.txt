project(encoding)

set(CXX_FLAGS_COMMON "${CXX_FLAGS_COMMON} -fno-exceptions -fno-rtti")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${CXX_FLAGS_COMMON}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${CXX_FLAGS_COMMON} -O3 -g0")

include_directories(
  ${v8source}
  ${v8source}/include
  ${ICU_INCLUDE_DIRS}
)

set(${PROJECT_NAME}_sources
  ${v8source}/third_party/inspector_protocol/encoding/encoding.cc
)

add_definitions(-DNVALGRIND)
add_definitions(-D__STDC_CONSTANT_MACROS)
add_definitions(-D__STDC_FORMAT_MACROS)
add_definitions(-D_GNU_SOURCE)

#if(${ARCHITECTURE} STREQUAL "x86_64")
#  add_definitions(-DV8_TARGET_ARCH_X64)
#elseif(${ARCHITECTURE} STREQUAL "i386" OR ${ARCHITECTURE} STREQUAL "i486" OR ${ARCHITECTURE} STREQUAL "i586"  OR ${ARCHITECTURE} STREQUAL "i686")
#  add_definitions(V8_TARGET_ARCH_IA32)
#endif()

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

