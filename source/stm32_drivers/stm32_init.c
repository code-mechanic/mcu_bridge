#include <mcu_bridge.h>
#include <mcu_cfg.h>

/* STM32 MCU header. Macro will be created as a part of CMakeLists.txt */
#include STM32_HAL_HEADER
#include <mcu_gpio.h>

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

status_t mcu_bridge_drivers_init(void);

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

status_t mcu_bridge_init(mcu_bridge_init_param_t* p_init_param)
{
    status_t status = STATUS_SUCCESS;

    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    if(HAL_Init() != HAL_OK) {
        status = STATUS_FAILURE;
    }

    if(status == STATUS_SUCCESS) {
        if((p_init_param != NULL) && (p_init_param->mcu_clock_config != NULL)) {
            status = p_init_param->mcu_clock_config();
        }
    }

    if(status == STATUS_SUCCESS) {
        status = mcu_bridge_drivers_init();
    }

    return status;
}

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                                Functions                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

status_t mcu_bridge_drivers_init(void)
{
    status_t status = STATUS_SUCCESS;

#ifdef MCU_CFG_GPIO_DRIVER_ENABLED
    if(status == STATUS_SUCCESS) {
        status = mcu_gpio_init();
    }
#endif /* MCU_CFG_GPIO_DRIVER_ENABLED */

    return status;
}

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                            Callback Handlers                             |
// |                                                                          |
// +--------------------------------------------------------------------------+
