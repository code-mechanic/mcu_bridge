#
# This file defines cmake variables specific to this product
#

set(MCU_BRIDGE_MCU pic16f)
set(MCU_BRIDGE_MCU_VERSION pic16f877a)
set(MCU_BRIDGE_RTOS nortos)

#
# Feature ON/OFF flags
#
set(MCU_BRIDGE_COMMON_ALGORITHM OFF)
set(MCU_BRIDGE_COMMON_CLI OFF)
set(MCU_BRIDGE_COMMON_CONTROLLERS OFF)
set(MCU_BRIDGE_COMMON_LOG OFF)
set(MCU_BRIDGE_COMMON_PROFILE OFF)
set(MCU_BRIDGE_COMMON_SW_WATCHDOG OFF)

#
# Test ON/OFF flags
#
set(MCU_BRIDGE_TEST OFF)
set(MCU_BRIDGE_TEST_BLINKY OFF)
set(MCU_BRIDGE_TEST_COMMON OFF)
set(MCU_BRIDGE_TEST_CPU_BENCHMARKS OFF)
set(MCU_BRIDGE_TEST_HELLO_WORLD OFF)
set(MCU_BRIDGE_TEST_HW OFF)
set(MCU_BRIDGE_TEST_LOG_AND_PROFILE OFF)
set(MCU_BRIDGE_TEST_MCU OFF)
set(MCU_BRIDGE_TEST_OSA OFF)

#
# Test MCU individual tests ON/OFF flags
#
set(MCU_BRIDGE_TEST_MCU_ADC OFF)
set(MCU_BRIDGE_TEST_MCU_DMA OFF)
set(MCU_BRIDGE_TEST_MCU_GPIO OFF)
set(MCU_BRIDGE_TEST_MCU_GPIO_LOOPBACK OFF)
set(MCU_BRIDGE_TEST_MCU_GPIO_SET_PIN_DIR OFF)
set(MCU_BRIDGE_TEST_MCU_I2C OFF)
set(MCU_BRIDGE_TEST_MCU_PWM OFF)
set(MCU_BRIDGE_TEST_MCU_PWM_ADC_DMA OFF)
set(MCU_BRIDGE_TEST_MCU_SPI OFF)
set(MCU_BRIDGE_TEST_MCU_UART OFF)
set(MCU_BRIDGE_TEST_MCU_WATCHDOG OFF)

#
# Configurations
#
list(APPEND MCU_BRIDGE_CONFIG_LIST pic16f877a_cfg_default)

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
