set(EXECUTABLE stm32_gpio)

add_executable(${EXECUTABLE} main.c)

target_link_libraries(
    ${EXECUTABLE}
    PRIVATE mcu_bridge_drivers
)

if(${MCU_BRIDGE_HW} STREQUAL "stm32")
    mcu_bridge_target_set_linker_script_and_memory_map_file(
        ${EXECUTABLE}
        ${CMAKE_CURRENT_SOURCE_DIR}/../stm32/STM32G474RETX_FLASH.ld
    )

    target_sources(
        ${EXECUTABLE}
        PRIVATE ${MCU_BRIDGE_PATH}/external/stm32/cmsis_device_g4/Source/Templates/system_stm32g4xx.c
        PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../stm32/startup_stm32g474retx.s
    )
endif()

# This function converts a cmake target executable file, e.g elf file into a
# format that can be flashed.
add_custom_command(
    TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${EXECUTABLE}.elf ${EXECUTABLE}.bin
)
