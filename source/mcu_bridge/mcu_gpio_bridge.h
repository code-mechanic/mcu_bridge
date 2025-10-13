#ifndef MCU_BRIDGE_H
#define MCU_BRIDGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <mcu_drivers/mcu_gpio.h>

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                          Definitions and Macros                          |
// |                                                                          |
// +--------------------------------------------------------------------------+

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                                 Typedefs                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                                 Extern's                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                                Functions                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

status_t mcu_gpio_bridge_init(void);
status_t mcu_gpio_bridge_deinit(void);
status_t mcu_gpio_bridge_config(uint32_t gpio_idx, mcu_gpio_config_t* p_config);
status_t mcu_gpio_bridge_read(uint32_t gpio_idx, mcu_gpio_pin_val_t* p_val);
status_t mcu_gpio_bridge_write(uint32_t gpio_idx, mcu_gpio_pin_val_t val);
status_t mcu_gpio_bridge_toggle(uint32_t gpio_idx);
status_t mcu_gpio_bridge_set_dir(uint32_t gpio_idx, mcu_gpio_pin_dir_t dir);
status_t mcu_gpio_bridge_get_dir(uint32_t gpio_idx, mcu_gpio_pin_dir_t* p_dir);

#ifdef __cplusplus
}
#endif

#endif /* MCU_BRIDGE_H */
