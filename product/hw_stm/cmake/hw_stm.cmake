#
# This file defines cmake variables specific to this product
#

set(MCU_BRIDGE_MCU stm32g4)
set(MCU_BRIDGE_MCU_VERSION stm32g474xx)
set(MCU_BRIDGE_RTOS ucos)

#
# Feature ON/OFF flags
#
set(MCU_BRIDGE_COMMON_ALGORITHM ON)
set(MCU_BRIDGE_COMMON_CLI ON)
set(MCU_BRIDGE_COMMON_CONTROLLERS ON)
set(MCU_BRIDGE_COMMON_LOG ON)
set(MCU_BRIDGE_COMMON_PROFILE ON)

#
# Test ON/OFF flags
#
set(MCU_BRIDGE_TEST ON)
set(MCU_BRIDGE_TEST_BLINKY ON)
set(MCU_BRIDGE_TEST_COMMON ON)
set(MCU_BRIDGE_TEST_CPU_BENCHMARKS ON)
set(MCU_BRIDGE_TEST_HELLO_WORLD ON)
set(MCU_BRIDGE_TEST_HW ON)
set(MCU_BRIDGE_TEST_LOG_AND_PROFILE ON)
set(MCU_BRIDGE_TEST_MCU ON)
set(MCU_BRIDGE_TEST_OSA ON)

#
# Test MCU individual tests ON/OFF flags
#
set(MCU_BRIDGE_TEST_MCU_ADC ON)
set(MCU_BRIDGE_TEST_MCU_DMA ON)
set(MCU_BRIDGE_TEST_MCU_DMA_TIM_TRIGERED_DMA OFF)
set(MCU_BRIDGE_TEST_MCU_DMA_M2M_LINK OFF)
set(MCU_BRIDGE_TEST_MCU_GPIO ON)
set(MCU_BRIDGE_TEST_MCU_GPIO_LOOPBACK ON)
set(MCU_BRIDGE_TEST_MCU_GPIO_NUCLEO_STM32G474 ON)
set(MCU_BRIDGE_TEST_MCU_GPIO_SET_PIN_DIR OFF)
set(MCU_BRIDGE_TEST_MCU_I2C ON)
set(MCU_BRIDGE_TEST_MCU_PWM OFF)
set(MCU_BRIDGE_TEST_MCU_PWM_ADC_DMA ON)
set(MCU_BRIDGE_TEST_MCU_SECURE_RAM OFF)
set(MCU_BRIDGE_TEST_MCU_SPIM OFF)
set(MCU_BRIDGE_TEST_MCU_UART ON)
set(MCU_BRIDGE_TEST_MCU_WATCHDOG ON)
set(MCU_BRIDGE_TEST_MCU_WATCHDOG_LAST OFF)

#
# Test HW individual tests ON/OFF flags
#
set(MCU_BRIDGE_TEST_HW_EEPROM OFF)
set(MCU_BRIDGE_TEST_HW_GPIO OFF)
set(MCU_BRIDGE_TEST_HW_BMS OFF)

#
# Test Common individual tests ON/OFF flags
#
set(MCU_BRIDGE_TEST_COMMON_ALGORITHM ON)
set(MCU_BRIDGE_TEST_COMMON_CLI ON)
set(MCU_BRIDGE_TEST_COMMON_COMMON ON)
set(MCU_BRIDGE_TEST_COMMON_SW_WATCHDOG ON)

#
# Configurations
#
list(APPEND MCU_BRIDGE_CONFIG_LIST nucleo_stm32g474_cfg_default)

#
# This function converts a cmake target executable file, e.g elf file into a
# format that can be flashed and booted by the MCU bootloader
#
# This function needs to be defined by every MCU_BRIDGE_HW cmake file since the
# exact command used to make a flashable binary is specific to that
# MCU_BRIDGE_HW
#
function(mcu_bridge_make_flash_image EXECUTABLE)
  add_custom_command(
    TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${EXECUTABLE}.elf ${EXECUTABLE}.bin)
endfunction()
