set(TARGET stm32_bridge_drivers)

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
    PRIVATE mcu_bridge_drivers
    PRIVATE stm32_hal_driver
)
