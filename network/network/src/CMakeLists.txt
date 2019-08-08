FILE(GLOB HEADER_FILES *.h *.hpp)
FILE(GLOB SOURCE_FILES *.cpp)

include_directories(
  ${PROJECT_DIR}
  ${Boost_INCLUDE_DIRS}
)

link_directories(
  ${Boost_LIBRARIES0}
)

add_library(network_static STATIC ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(network_static PROPERTIES OUTPUT_NAME network)

add_library(network_obj OBJECT ${HEADER_FILES} ${SOURCE_FILES})
set_property(TARGET network_obj PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(network_static_pic STATIC $<TARGET_OBJECTS:network_obj>)
add_library(network SHARED $<TARGET_OBJECTS:network_obj>)

