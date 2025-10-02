#ifndef STM32_GPIO_H
#define STM32_GPIO_H

#include <mcu_gpio.h>

/* This file will be generated as a part of the CMake build process in build directory */
#include <stm32_config.h>

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} stm32_gpio_ctx_t;

status_t stm32_gpio_ctx_init(stm32_gpio_ctx_t* ctx, GPIO_TypeDef* port, uint16_t pin);
status_t stm32_gpio_get_gpio_ops(const mcu_gpio_ops_t* p_ops);

#endif
