project(source)

message("CMAKE_BINARY_DIR: " ${CMAKE_BINARY_DIR})

include(ExternalProject)

set(depot_tools_git "https://chromium.googlesource.com/chromium/tools/depot_tools.git")
set(depot_tools_dir "${CMAKE_BINARY_DIR}/depot_tools")

set(v8_git "https://chromium.googlesource.com/v8/v8.git")
set(v8_dir "${CMAKE_BINARY_DIR}/v8")

ExternalProject_Add(depot_tools
  GIT_REPOSITORY ${depot_tools_git}
  SOURCE_DIR ${depot_tools_dir} 
  CONFIGURE_COMMAND  cmake -E echo "Skipping configure step."
  BUILD_COMMAND cmake -E echo "Skipping build step."
  INSTALL_COMMAND cmake -E echo "Skipping install step."
)

ExternalProject_Add(depot_tools
  GIT_REPOSITORY ${v8_git}
  SOURCE_DIR ${v8_dir} 
  CONFIGURE_COMMAND  cmake -E echo "Skipping configure step."
  BUILD_COMMAND cmake -E echo "Skipping build step."
  INSTALL_COMMAND cmake -E echo "Skipping install step."
)

add_custom_target(source ALL
  DEPENDS depot_tools
  COMMAND /bin/bash ${solution_dir}/scripts/v8build.sh "${v8source}" "${depot_tools_dir}"
)

message("CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR})
message("CMAKE_INSTALL_INCLUDEDIR: " ${CMAKE_INSTALL_INCLUDEDIR})

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/v8.h
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/v8-platform.h
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/v8-wasm-trap-handler-posix.h
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/v8-profiler.h
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/v8-version-string.h
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/v8-testing.h
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/v8-internal.h
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/v8-version.h
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/v8-inspector.h
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/v8-wasm-trap-handler-win.h
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/v8-util.h
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/v8-inspector-protocol.h
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/v8.h
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/v8config.h
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/v8-value-serializer-version.h
  DESTINATION include/v8
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/libplatform/libplatform-export.h
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/libplatform/v8-tracing.h
  ${CMAKE_CURRENT_BINARY_DIR}/v8/include/libplatform/libplatform.h
  DESTINATION include/v8/libplatform
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/v8/out/x64.release/libv8_debug_helper.so
  ${CMAKE_CURRENT_BINARY_DIR}/v8/out/x64.release/libv8_for_testing.so
  ${CMAKE_CURRENT_BINARY_DIR}/v8/out/x64.release/libv8_libbase.so
  ${CMAKE_CURRENT_BINARY_DIR}/v8/out/x64.release/libv8_libplatform.so
  ${CMAKE_CURRENT_BINARY_DIR}/v8/out/x64.release/libv8.so
  DESTINATION usr/lib/x86_64-linux-gnu/v8/
)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/v8/out/x64.release/libc++.so
  DESTINATION . RENAME usr/lib/x86_64-linux-gnu/v8/libc++_v8.so
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/v8/out/x64.release/libicui18n.so
  DESTINATION . RENAME usr/lib/x86_64-linux-gnu/v8/libicui18n_v8.so
)

install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/v8/out/x64.release/libicuuc.so
  DESTINATION . RENAME usr/lib/x86_64-linux-gnu/v8/libicuuc_v8.so
)
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/v8/out/x64.release/d8
  DESTINATION usr/bin
)
