file(GLOB HEADER_FILES "*.h *.hpp")
file(GLOB SOURCE_FILES "*.cpp")

project(avrotest)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
  ${AVROCPP_INCLUDE_DIR}
  ../include
  ./
)

target_link_libraries(${PROJECT_NAME} PRIVATE
  ${JSON-C_LIBRARY}
  ${AVROCPP_LIBRARIES}
  nlohmann_json::nlohmann_json
  Boost::boost
  Boost::filesystem
  Boost::iostreams
  Boost::program_options
  Boost::regex
  Boost::system
  ZLIB::ZLIB
)
