file(GLOB HEADER_FILES "*.h *.hpp")
file(GLOB SOURCE_FILES "*.cpp")

project(avrotest)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
  ${AVROCPP_INCLUDE_DIR}
  ${NLOHMANNJSON_ROOT}/include
  ../include
  ./
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  ${JSON-C_LIBRARY}
  ${AVROCPP_LIBRARIES}
)
