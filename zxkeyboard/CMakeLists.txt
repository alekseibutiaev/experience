# STM32 Minimal CMake project for C/C++ projects
cmake_minimum_required(VERSION 3.12)
###############################################################################
# Set project name and source code folder location
project(zxkeyboard)
set(PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/project)

option(BOARD_NUCLEO "type of board" ON)
option(DUMP_ASM "Create full assembly of final executable" OFF)
option(MCU "MCU type F105R8, F105RB, F105RC, F107RB, F107RC. F105R8 by default" "F105R8")

# Set microcontroller information
set(MCU_FAMILY STM32F1xx)
set(DEVICE STM32${MCU})
set(MCU_LINKER_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/linker/STM32${MCU}Tx_FLASH.ld)
if (${MCU} STREQUAL "F105R8" OR ${MCU} STREQUAL "F105RB" OR ${MCU} STREQUAL "F105RC")
  set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/startup/startup_stm32f105xc.s)
  set(MCU_MODEL STM32F105xC)
elseif (${MCU} STREQUAL "F107RB" OR ${MCU} STREQUAL "F107RC")
  set(STARTUP_SCRIPT ${CMAKE_CURRENT_SOURCE_DIR}/startup/startup_stm32f107xc.s)
  set(MCU_MODEL STM32F107xC)
else()
    message(FATAL_ERROR "uscupported MCU " ${MCU})
endif()
message("MCU_LINKER_SCRIPT" ${MCU_LINKER_SCRIPT})
message("STARTUP_SCRIPT" ${STARTUP_SCRIPT})
set(JLINKEXE "/opt/SEGGER/JLink/JLinkExe")
set(ST-UTILS "/usr/bin/st-flash")
set(CPU_PARAMETERS -mcpu=cortex-m3 -mthumb -mfloat-abi=soft)

enable_language(C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
#set(CMAKE_EXE_LINKER_FLAGS "--specs=aprofile-ve.specs" CACHE INTERNAL "")

###############################################################################

set(EXECUTABLE ${CMAKE_PROJECT_NAME})

set(STM32CUBEMX_INCLUDE_DIRECTORIES
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/${MCU_FAMILY}_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/${MCU_FAMILY}_HAL_Driver/Inc/Legacy
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Device/ST/${MCU_FAMILY}/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/ST/STM32_USB_Host_Library/Core/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/ST/STM32_USB_Host_Library/Class/HID/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/project
    )

set(PROJECT_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE STM32CUBEMX_SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/Core/Src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Drivers/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/ST/STM32_USB_Host_Library/Core/Src/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Middlewares/ST/STM32_USB_Host_Library/Class/HID/Src/*.c)

file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS
    ${PROJECT_DIR}/*.cpp
    ${PROJECT_DIR}/*.c)

add_executable(${EXECUTABLE}
    ${STM32CUBEMX_SOURCES} 
    ${PROJECT_SOURCES}
    ${STARTUP_SCRIPT})

target_compile_definitions(${EXECUTABLE} PRIVATE
    $<$<CONFIG:Debug>:DEBUG>
    $<$<BOOL:${BOARD_NUCLEO}>:NUCLEO>
    ${MCU_MODEL}
    USE_HAL_DRIVER)

#target_include_directories(${EXECUTABLE} SYSTEM PRIVATE
#    ${STM32CUBEMX_INCLUDE_DIRECTORIES})
target_include_directories(${EXECUTABLE} PRIVATE
    ${STM32CUBEMX_INCLUDE_DIRECTORIES})

target_include_directories(${EXECUTABLE} PRIVATE
    ${PROJECT_INCLUDE_DIRECTORIES})

###############################################################################

target_compile_options(${EXECUTABLE} PRIVATE
    ${CPU_PARAMETERS}
    -Wall
    -fstack-usage
    -fdata-sections
    -ffunction-sections
    $<$<COMPILE_LANGUAGE:CXX>:
        -Wconversion # STM libraries!
        -Wno-volatile
        -Wold-style-cast
        -Wuseless-cast
        -Wsuggest-override>
    $<$<CONFIG:Debug>:-O0 -g3>
    $<$<CONFIG:Release>:-Os -g0>)

target_link_options(${EXECUTABLE} PRIVATE
    -T${MCU_LINKER_SCRIPT}
    ${CPU_PARAMETERS}
    -Wl,-Map=${CMAKE_PROJECT_NAME}.map
    -Wl,--start-group
    -lc
    -lm
    -Wl,--end-group
    -Wl,--print-memory-usage
    )

# The last command can take a couple of seconds on larger project, usefull for debugging
add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
    COMMAND ${CMAKE_SIZE} $<TARGET_FILE:${EXECUTABLE}>
    COMMAND ${CMAKE_OBJCOPY} -O ihex $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.hex
    COMMAND ${CMAKE_OBJCOPY} -O binary $<TARGET_FILE:${EXECUTABLE}> ${EXECUTABLE}.bin)

if (${DUMP_ASM})
    add_custom_command(TARGET ${EXECUTABLE} POST_BUILD
        COMMAND ${CMAKE_OBJDUMP} -D $<TARGET_FILE:${EXECUTABLE}> > ${EXECUTABLE}.s)
endif()

add_custom_command(OUTPUT jlink_cmd_script
    COMMAND echo "device ${DEVICE}" >> jlink_cmd_script
    COMMAND echo "if swd" >> jlink_cmd_script
    COMMAND echo "Speed 4000" >> jlink_cmd_script
    COMMAND echo "LoadFile ${CMAKE_BINARY_DIR}/${EXECUTABLE}.bin 0x08000000" >> jlink_cmd_script
    COMMAND echo "Exit" >> jlink_cmd_script
    VERBATIM
)

add_custom_target(jlink_upload DEPENDS ${EXECUTABLE} jlink_cmd_script
    COMMAND cat jlink_cmd_script
    COMMAND ${JLINKEXE} -CommanderScript jlink_cmd_script
)

add_custom_target(stlink_upload DEPENDS ${EXECUTABLE}
    COMMAND echo "run ${ST-UTILS} write ${CMAKE_BINARY_DIR}/${EXECUTABLE}.bin 0x08000000"
    COMMAND ${ST-UTILS} write ${CMAKE_BINARY_DIR}/${EXECUTABLE}.bin 0x08000000
)
