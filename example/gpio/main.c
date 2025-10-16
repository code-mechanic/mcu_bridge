#include "mcu_bridge.h"

#define LED_IDX (0U)

int main(void) {
    status_t status = STATUS_SUCCESS;

    /* Call this before using MCU Bridge APIs */
    status = mcu_bridge_init(NULL);
    if(status != STATUS_SUCCESS) {
        mcu_bridge_status_error_handler();
    }

    mcu_gpio_config_t led_config; 
    mcu_gpio_config_set_default(LED_IDX, &led_config);

    led_config.pin = mcu_gpio_create_pin(0 , 5);
    led_config.pin_dir = MCU_GPIO_PIN_DIR_OUTPUT;
    led_config.op_pin_initial_val = MCU_GPIO_PIN_VAL_LOW;
    led_config.op_pin_speed = MCU_GPIO_PIN_SPEED_LOW;
    status = mcu_gpio_config(LED_IDX, &led_config);
    if(status != STATUS_SUCCESS) {
        mcu_bridge_status_error_handler();
    }

    while(1) {
        status = mcu_gpio_write(LED_IDX, MCU_GPIO_PIN_VAL_HIGH);
        if(status != STATUS_SUCCESS) {
            mcu_bridge_status_error_handler();
        }

        status = mcu_gpio_write(LED_IDX, MCU_GPIO_PIN_VAL_LOW);
        if(status != STATUS_SUCCESS) {
            mcu_bridge_status_error_handler();
        }
    }

    return 0;
}
