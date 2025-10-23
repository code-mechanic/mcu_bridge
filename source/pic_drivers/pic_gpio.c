#include <mcu_bridge_cfg.h>
#ifdef MCU_BRIDGE_CFG_GPIO_DRIVER_ENABLED

#include <mcu_gpio_bridge.h>
#include <common/utils.h>

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                          Definitions and Macros                          |
// |                                                                          |
// +--------------------------------------------------------------------------+

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                                 Typedefs                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                           Function Prototypes                            |
// |                                                                          |
// +--------------------------------------------------------------------------+

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                          Variable Declarations                           |
// |                                                                          |
// +--------------------------------------------------------------------------+

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                                Functions                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

status_t mcu_gpio_bridge_init(void)
{
    status_t status = STATUS_SUCCESS;

    return status;
}

status_t mcu_gpio_bridge_deinit(void)
{
    status_t status = STATUS_SUCCESS;
    /* Nothing to do here */
    return status;
}

status_t mcu_gpio_bridge_config(uint32_t gpio_idx, mcu_gpio_config_t* p_config)
{
    status_t status = STATUS_SUCCESS;

    return status;
}

status_t mcu_gpio_bridge_read(uint32_t gpio_idx, mcu_gpio_pin_val_t* p_val)
{
    status_t status = STATUS_SUCCESS;

    return status;
}

status_t mcu_gpio_bridge_write(uint32_t gpio_idx, mcu_gpio_pin_val_t val)
{
    status_t status = STATUS_SUCCESS;

    return status;
}

status_t mcu_gpio_bridge_toggle(uint32_t gpio_idx)
{
    status_t status = STATUS_SUCCESS;

    return status;
}

status_t mcu_gpio_bridge_set_dir(uint32_t gpio_idx, mcu_gpio_pin_dir_t dir)
{
    status_t status = STATUS_SUCCESS;

    return status;
}

status_t mcu_gpio_bridge_get_dir(uint32_t gpio_idx, mcu_gpio_pin_dir_t* p_dir)
{
    status_t status = STATUS_SUCCESS;

    return status;
}

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                                Functions                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                            Callback Handlers                             |
// |                                                                          |
// +--------------------------------------------------------------------------+

#endif /* MCU_BRIDGE_CFG_GPIO_DRIVER_ENABLED */
