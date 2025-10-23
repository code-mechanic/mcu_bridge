#include <mcu_bridge.h>

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

static status_t mcu_bridge_drivers_init(void);

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

void mcu_bridge_status_error_handler(void)
{
}

void mcu_bridge_delay_ms(uint32_t delay_ms)
{
}

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                                Functions                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

static status_t mcu_bridge_drivers_init(void)
{
    status_t status = STATUS_SUCCESS;

#ifdef MCU_BRIDGE_CFG_GPIO_DRIVER_ENABLED
    if(status == STATUS_SUCCESS) {
        status = mcu_gpio_init();
    }
#endif /* MCU_BRIDGE_CFG_GPIO_DRIVER_ENABLED */

    return status;
}

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                            Callback Handlers                             |
// |                                                                          |
// +--------------------------------------------------------------------------+
