
add_custom_command(
  OUTPUT libraries_extras.bin
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/v8build/gen
  COMMAND ${PYTHON_EXECUTABLE} ${v8source}/tools/js2c.py
    ${CMAKE_BINARY_DIR}/v8build/gen/extras-libraries.cc EXTRAS
    --startup_blob ${CMAKE_BINARY_DIR}/v8build/gen/libraries_extras.bin
)

add_custom_target(libraries_extras DEPENDS libraries_extras.bin)

add_custom_command(
  OUTPUT natives_blob.bin
  DEPENDS libraries_extras
  COMMAND python ${v8source}/tools/concatenate-files.py ${CMAKE_BINARY_DIR}/v8build/gen/extras-libraries.bin ${CMAKE_BINARY_DIR}/v8build/natives_blob.bin
)

add_custom_target(natives_blob.bin DEPENDS natives_blob.bin)

add_custom_command(
  OUTPUT system_googletest
  COMMAND /bin/bash ${solution_dir}/scripts/system_googletest.sh "${v8source}"
  COMMAND ${CMAKE_COMMAND} -E touch system_googletest
)

add_custom_target(use_system_googletest DEPENDS system_googletest)

add_custom_command(
  OUTPUT rename_debug_cmd
  COMMAND /bin/bash ${solution_dir}/scripts/rename_debug.sh "${v8source}"
  COMMAND ${CMAKE_COMMAND} -E touch rename_debug_cmd
)

add_custom_target(rename_debug DEPENDS rename_debug_cmd)

