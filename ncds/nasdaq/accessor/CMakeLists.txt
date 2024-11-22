file(GLOB HEADER_FILES "./*.h *.hpp")
file(GLOB SOURCE_FILES "sources/*.cpp")

project(accessor)

include_directories(
  ${CURL_INCLUDE_DIR}
  ${AVROCPP_INCLUDE_DIR}
  ${RDKAFKA_INCLUDE_DIR}
  ${RDKAFKACPP_INCLUDE_DIR}
  ${SPDLOG_INCLUDE_DIR}
  ${NLOHMANNJSON_ROOT}/include
  ../
  ./
)

#add_compile_options(-Wignored-qualifiers)

add_library(${PROJECT_NAME}_static STATIC ${SOURCE_FILES})
