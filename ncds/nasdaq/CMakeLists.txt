file(GLOB HEADER_FILES "*.h" "*.hpp" "tw/*.h" "tw/*.hpp" "accessor/*.h" "accessor/*.hpp")
file(GLOB SOURCE_FILES "sources/*.cpp" "tw/sources/*.cpp" "accessor/sources/*.cpp")

message("HEADER_FILES: " ${HEADER_FILES})
message("SOURCE_FILES: " ${SOURCE_FILES})

project(nasdaq)

include_directories(
  ${CURL_INCLUDE_DIR}
  ${AVROCPP_INCLUDE_DIR}
  ${RDKAFKA_INCLUDE_DIR}
  ${RDKAFKACPP_INCLUDE_DIR}
  ${SPDLOG_INCLUDE_DIR}
  ${NLOHMANNJSON_ROOT}/include
##  ${CMAKE_CURRENT_SOURCE_DIR}/accessor
##  ${CMAKE_CURRENT_SOURCE_DIR}/dom
  ./
)

add_library(${PROJECT_NAME}_static STATIC ${SOURCE_FILES})
target_compile_options(${PROJECT_NAME}_static PRIVATE -Wall -Werror)

add_subdirectory(test)
