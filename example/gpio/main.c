#include "stm32_gpio.h"

int main() {
    status_t status;
    stm32_gpio_ctx_t gpio_ctx_1;
    mcu_gpio_ops_t gpio_ops;
    mcu_gpio_handle_t gpio_handle;

    // Example port and pin initialization
    status = stm32_gpio_ctx_init(&gpio_ctx_1, (uint16_t *)0x40020000, 5);

    if(status == STATUS_SUCCESS) {
        stm32_gpio_get_gpio_ops(&gpio_ops);
    }

    if(status == STATUS_SUCCESS) {
        mcu_gpio_init_handle(&gpio_handle, &gpio_ops, &gpio_ctx_1);
    }

    mcu_gpio_pin_val_t val;
    mcu_gpio_read(&gpio_handle, &val);

    return 0;
}