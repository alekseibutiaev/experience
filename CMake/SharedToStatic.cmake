
function(SHARED_TO_STATIC OUT_STATIC_LIBRARY_LIST IN_SHARED_LIBRARY_LIST)
  foreach(component ${IN_SHARED_LIBRARY_LIST})
    get_filename_component(clear_library_name ${component} NAME_WE)
    string(CONCAT static_lib "-l:" ${clear_library_name} ".a")
    list(APPEND liblist ${static_lib})
  endforeach()
  set(${OUT_STATIC_LIBRARY_LIST} ${liblist} PARENT_SCOPE)
endfunction()
