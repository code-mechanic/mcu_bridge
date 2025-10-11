set(TARGET ${MCU_BRIDGE_HW}_bridge_drivers)

# create stm32_bridge_drivers library
add_library(
    ${TARGET}
    stm32_init.c
    stm32_gpio.c
)

target_compile_definitions(
    ${TARGET}
    PUBLIC STM32_HAL_HEADER="${MCU_BRIDGE_MCU}_hal.h"
    PUBLIC STM32_HAL_GPIO_HEADER="${MCU_BRIDGE_MCU}_hal_gpio.h"
    PUBLIC STM32_HAL_RCC_HEADER="${MCU_BRIDGE_MCU}_hal_rcc.h"
    PUBLIC STM32_CMSIS_DEVICE_HEADER="${MCU_BRIDGE_MCU}.h"
)

target_link_libraries(
    ${TARGET}
    PUBLIC mcu_bridge_cfg      # To access macro from config/mcu_bridge_cfg.h
    PUBLIC ${MCU_BRIDGE_HW}_bridge_headers  # To access source/mcu_bridge folder
    PUBLIC ${MCU_BRIDGE_MCU}_hal_driver     # Core dependency for stm32
)
