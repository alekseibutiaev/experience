
#[1/1310] python ../../tools/js2c.py gen/extras-libraries.cc EXTRAS --startup_blob gen/libraries_extras.bin
#[2/1310] touch obj/js2c_extras.stamp
#[3/1310] python ../../tools/concatenate-files.py gen/libraries_extras.bin natives_blob.bin
#[4/1310] touch obj/natives_blob.stamp


add_custom_command(
  OUTPUT libraries_extras_bin
  COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/v8build/gen
  COMMAND ${PYTHON_EXECUTABLE} ${v8source}/tools/js2c.py
    ${CMAKE_BINARY_DIR}/v8build/gen/extras-libraries.cc EXTRAS
    --startup_blob ${CMAKE_BINARY_DIR}/v8build/gen/libraries_extras.bin
  COMMAND ${CMAKE_COMMAND} -E touch libraries_extras_bin
)

add_custom_target(libraries_extras DEPENDS libraries_extras_bin)

#add_custom_command(
#  OUTPUT natives_blob_bin
#  DEPENDS libraries_extras
#  COMMAND ${PYTHON_EXECUTABLE} ${v8source}/tools/concatenate-files.py
#    ${CMAKE_BINARY_DIR}/v8build/gen/extras_libraries.bin
#    ${CMAKE_BINARY_DIR}/v8build/gen/natives_blob.bin
#  COMMAND ${CMAKE_COMMAND} -E touch natives_blob_bin
#)

#add_custom_target(natives_blob DEPENDS natives_blob_bin)

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

add_custom_command(
  OUTPUT embedded_s
  DEPENDS mksnapshot
  COMMAND ${PYTHON_EXECUTABLE} ${v8source}/tools/run.py
    ${CMAKE_BINARY_DIR}/v8build/mksnapshot/mksnapshot
    --target_os=linux --target_arch=x64 --embedded_src
    ${CMAKE_BINARY_DIR}/v8build/gen/embedded.S
    --embedded_variant Default --random-seed 314159265
    --startup_blob ${CMAKE_BINARY_DIR}/v8build/gen/snapshot_blob.bin
    --no-native-code-counters
  COMMAND ${CMAKE_COMMAND} -E touch embedded_s
)

add_custom_target(run_mksnapshot DEPENDS embedded_s)

