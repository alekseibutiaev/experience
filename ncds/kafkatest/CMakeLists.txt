file(GLOB HEADER_FILES "*.h" "*.hpp")
file(GLOB SOURCE_FILES "*.cpp")

project(kafkatest)

add_definitions(-D__USE_POSIX)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CURL_INCLUDE_DIR}
  ${AVROCPP_INCLUDE_DIR}
  ${RDKAFKA_INCLUDE_DIR}
  ${RDKAFKACPP_INCLUDE_DIR}
  ${NLOHMANNJSON_ROOT}/include
  ../nasdaq
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  nasdaq_static
  ${AVROCPP_LIBRARIES}
  ${CURL_LIBRARIES}
  ${RDKAFKA_LIBRARIES}
  ${RDKAFKACPP_LIBRARIES}
  ${JSON-C_LIBRARY}
  nlohmann_json::nlohmann_json
  Boost::boost
  Boost::filesystem
  Boost::iostreams
  Boost::program_options
  Boost::regex
  Boost::system
  ZLIB::ZLIB
)
