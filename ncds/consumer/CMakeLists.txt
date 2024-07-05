file(GLOB HEADER_FILES "*.h *.hpp")
file(GLOB SOURCE_FILES "*.cpp")

project(consumer)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CURL_INCLUDE_DIR}
  ${AVROCPP_INCLUDE_DIR}
  ${RDKAFKA_INCLUDE_DIR}
  ${RDKAFKACPP_INCLUDE_DIR}
  ${SPDLOG_INCLUDE_DIR}
#  ${NLOHMANNJSON_ROOT}/include
  ../include
  ./
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  ${CURL_LIBRARIES}
  kafka
  ${JSON-C_LIBRARY}
  ${RDKAFKA_LIBRARIES}
  ${RDKAFKACPP_LIBRARIES}
  ${AVROCPP_LIBRARIES}
)
