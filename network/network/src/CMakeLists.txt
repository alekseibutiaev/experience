file(GLOB HEADER_FILES *.h *.hpp)
file(GLOB SOURCE_FILES *.cpp)

include_directories(
  ${PROJECT_DIR}
  ${Boost_INCLUDE_DIRS}
)

link_directories(
  ${Boost_LIBRARIES}
  Threads::Threads
)

add_library(${PROJECT_NAME}_static STATIC ${HEADER_FILES} ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

add_library(${PROJECT_NAME}_obj OBJECT ${HEADER_FILES} ${SOURCE_FILES})
set_property(TARGET ${PROJECT_NAME}_obj PROPERTY POSITION_INDEPENDENT_CODE 1)

add_library(${PROJECT_NAME}_static_pic STATIC $<TARGET_OBJECTS:${PROJECT_NAME}_obj>)
add_library(${PROJECT_NAME} SHARED $<TARGET_OBJECTS:${PROJECT_NAME}_obj>)
