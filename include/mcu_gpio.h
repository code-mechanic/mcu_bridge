#ifndef MCU_GPIO_H
#define MCU_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <status.h>

typedef enum mcu_gpio_pin_val_t_ {
    MCU_GPIO_PIN_VAL_LOW  = 0u,
    MCU_GPIO_PIN_VAL_HIGH = 1u
} mcu_gpio_pin_val_t;

typedef enum mcu_gpio_pin_dir_t_ {
    MCU_GPIO_PIN_DIR_INPUT  = 0u,
    MCU_GPIO_PIN_DIR_OUTPUT = 1u
} mcu_gpio_pin_dir_t;

typedef struct mcu_gpio_ops_t_ {
    /* Base operations */
    status_t (*read)(void* mcu_gpio_ctx, mcu_gpio_pin_val_t* p_val);
    status_t (*write)(void* mcu_gpio_ctx, mcu_gpio_pin_val_t val);
    status_t (*set_dir)(void* mcu_gpio_ctx, mcu_gpio_pin_dir_t dir);
    status_t (*get_dir)(void* mcu_gpio_ctx, mcu_gpio_pin_dir_t* p_dir);
} mcu_gpio_ops_t;

typedef struct mcu_gpio_handle_t_ mcu_gpio_handle_t;

status_t mcu_gpio_init_handle(mcu_gpio_handle_t* p_gpio_handle, mcu_gpio_ops_t* p_ops, void* mcu_gpio_ctx);
status_t mcu_gpio_read(mcu_gpio_handle_t* p_gpio_handle, mcu_gpio_pin_val_t* p_val);
status_t mcu_gpio_write(mcu_gpio_handle_t* p_gpio_handle, mcu_gpio_pin_val_t val);
status_t mcu_gpio_set_dir(mcu_gpio_handle_t* p_gpio_handle, mcu_gpio_pin_dir_t dir);
status_t mcu_gpio_get_dir(mcu_gpio_handle_t* p_gpio_handle, mcu_gpio_pin_dir_t* p_dir);

#ifdef __cplusplus
}
#endif

#endif /* MCU_GPIO_H */
