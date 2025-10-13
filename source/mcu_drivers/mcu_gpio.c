#include <mcu_bridge_cfg.h>
#ifdef MCU_BRIDGE_CFG_GPIO_DRIVER_ENABLED

#include <stdbool.h>
#include <mcu_gpio_bridge.h>

#if !defined(MCU_BRIDGE_CFG_GPIO_MAX_PORTS_AVAILABLE)
#error "MCU_BRIDGE_CFG_GPIO_MAX_PORTS_AVAILABLE is not defined in mcu_bridge_cfg.h"
#endif

#if !defined(MCU_BRIDGE_CFG_GPIO_MAX_PINS_PER_PORT)
#error "MCU_BRIDGE_CFG_GPIO_MAX_PINS_PER_PORT is not defined in mcu_bridge_cfg.h"
#endif

#if !defined(MCU_BRIDGE_CFG_GPIO_MAX_PINS_TO_USE)
#error "MCU_BRIDGE_CFG_GPIO_MAX_PINS_TO_USE is not defined in mcu_bridge_cfg.h"
#endif

#if(MCU_BRIDGE_CFG_GPIO_MAX_PORTS_AVAILABLE <= 0U)
#error "MCU_BRIDGE_CFG_GPIO_MAX_PORTS_AVAILABLE should be greater than 0"
#endif

#if(MCU_BRIDGE_CFG_GPIO_MAX_PINS_PER_PORT <= 0U)
#error "MCU_BRIDGE_CFG_GPIO_MAX_PINS_PER_PORT should be greater than 0"
#endif

#if(MCU_BRIDGE_CFG_GPIO_MAX_PINS_TO_USE <= 0U)
#error "MCU_BRIDGE_CFG_GPIO_MAX_PINS_TO_USE should be greater than 0"
#endif

#if(MCU_BRIDGE_CFG_GPIO_MAX_PINS_TO_USE > \
    (MCU_BRIDGE_CFG_GPIO_MAX_PORTS_AVAILABLE * MCU_BRIDGE_CFG_GPIO_MAX_PINS_PER_PORT))
#error \
    "MCU_BRIDGE_CFG_GPIO_MAX_PINS_TO_USE should be less than MCU_BRIDGE_CFG_GPIO_MAX_PORTS_AVAILABLE * MCU_BRIDGE_CFG_GPIO_MAX_PINS_PER_PORT"
#endif

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                          Definitions and Macros                          |
// |                                                                          |
// +--------------------------------------------------------------------------+

#define MCU_GPIO_CONFIG_DEFAULT_PIN           (0U)
#define MCU_GPIO_CONFIG_DEFAULT_PIN_DIR       (MCU_GPIO_PIN_DIR_OUTPUT)
#define MCU_GPIO_CONFIG_DEFAULT_PIN_VAL       (MCU_GPIO_PIN_VAL_LOW)
#define MCU_GPIO_CONFIG_DEFAULT_PIN_PULL      (MCU_GPIO_PIN_PULL_INVALID)
#define MCU_GPIO_CONFIG_DEFAULT_PIN_TRIG_TYPE (MCU_GPIO_PIN_INTR_TRIG_TYPE_INVALID)
#define MCU_GPIO_CONFIG_DEFAULT_PIN_SPEED     (MCU_GPIO_PIN_SPEED_INVALID)

#define IS_MCU_GPIO_PIN_VAL(__VAL__) (((__VAL__) == MCU_GPIO_PIN_VAL_LOW) || ((__VAL__) == MCU_GPIO_PIN_VAL_HIGH))

#define IS_MCU_GPIO_PIN_DIR(__DIR__) (((__DIR__) == MCU_GPIO_PIN_DIR_INPUT) || ((__DIR__) == MCU_GPIO_PIN_DIR_OUTPUT))

#define IS_MCU_GPIO_PIN_INTR_TRIG_TYPE(__TYPE__) \
    (((__TYPE__) > MCU_GPIO_PIN_INTR_TRIG_TYPE_INVALID) && ((__TYPE__) < MCU_GPIO_PIN_INTR_TRIG_TYPE_MAX))

#define IS_MCU_GPIO_PIN_PULL(__PULL__) \
    (((__PULL__) > MCU_GPIO_PIN_PULL_INVALID) && ((__PULL__) < MCU_GPIO_PIN_PULL_MAX))

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                                 Typedefs                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

typedef struct mcu_gpio_obj_t_ {
    /* Flag which will make sure mcu_gpio_*_ops_t are not NULL. */
    bool is_initialized;
} mcu_gpio_obj_t;

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                           Function Prototypes                            |
// |                                                                          |
// +--------------------------------------------------------------------------+

static status_t mcu_gpio_sanity_check(void);
static status_t mcu_gpio_config_check(mcu_gpio_config_t* p_config);

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                          Variable Declarations                           |
// |                                                                          |
// +--------------------------------------------------------------------------+

static mcu_gpio_obj_t g_mcu_gpio_obj = {
    .is_initialized = false,
};

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                                Functions                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

status_t mcu_gpio_init(void)
{
    status_t status = STATUS_SUCCESS;

    if(g_mcu_gpio_obj.is_initialized == false) {
        if(status == STATUS_FAILURE) {
            status = mcu_gpio_bridge_init();
            if(status == STATUS_FAILURE) {
                g_mcu_gpio_obj.is_initialized = true;
            } else {
                status = STATUS_MCU_INIT_DRIVER_FAILURE;
            }
        }
    }

    return status;
}

status_t mcu_gpio_deinit(void)
{
    status_t status = STATUS_SUCCESS;

    status = mcu_gpio_bridge_deinit();

    return status;
}

status_t mcu_gpio_config_set_default(uint32_t gpio_idx, mcu_gpio_config_t* p_config)
{
    status_t status = STATUS_SUCCESS;

    p_config->pin                = MCU_GPIO_CONFIG_DEFAULT_PIN;
    p_config->pin_dir            = MCU_GPIO_CONFIG_DEFAULT_PIN_DIR;
    p_config->op_pin_initial_val = MCU_GPIO_CONFIG_DEFAULT_PIN_VAL;
    p_config->op_pin_speed       = MCU_GPIO_CONFIG_DEFAULT_PIN_SPEED;
    p_config->ip_pin_pull        = MCU_GPIO_CONFIG_DEFAULT_PIN_PULL;
    p_config->ip_pin_trig_type   = MCU_GPIO_CONFIG_DEFAULT_PIN_TRIG_TYPE;
    p_config->isr_param.isr      = NULL;
    p_config->isr_param.p_arg    = NULL;
    p_config->config_callback    = NULL;

    return status;
}

status_t mcu_gpio_config(uint32_t gpio_idx, mcu_gpio_config_t* p_config)
{
    status_t status = STATUS_SUCCESS;

    status = mcu_gpio_config_check(p_config);

    if(status == STATUS_SUCCESS) {
        status = mcu_gpio_bridge_config(gpio_idx, p_config);
    }

    return status;
}

status_t mcu_gpio_read(uint32_t gpio_idx, mcu_gpio_pin_val_t* p_val)
{
    status_t status = mcu_gpio_sanity_check();

    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, p_val);

    if(status == STATUS_SUCCESS) {
        status = mcu_gpio_bridge_read(gpio_idx, p_val);
    }

    return status;
}

status_t mcu_gpio_write(uint32_t gpio_idx, mcu_gpio_pin_val_t val)
{
    status_t status = mcu_gpio_sanity_check();

    if(status == STATUS_SUCCESS) {
        status = mcu_gpio_bridge_write(gpio_idx, val);
    }

    return status;
}

status_t mcu_gpio_toggle(uint32_t gpio_idx)
{
    status_t status = mcu_gpio_sanity_check();

    if(status == STATUS_SUCCESS) {
        status = mcu_gpio_bridge_toggle(gpio_idx);
    }

    return status;
}

status_t mcu_gpio_set_dir(uint32_t gpio_idx, mcu_gpio_pin_dir_t dir)
{
    status_t status = mcu_gpio_sanity_check();

    if(status == STATUS_SUCCESS) {
        status = mcu_gpio_bridge_set_dir(gpio_idx, dir);
    }

    return status;
}

status_t mcu_gpio_get_dir(uint32_t gpio_idx, mcu_gpio_pin_dir_t* p_dir)
{
    status_t status = mcu_gpio_sanity_check();

    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, p_dir);

    if(status == STATUS_SUCCESS) {
        status = mcu_gpio_bridge_get_dir(gpio_idx, p_dir);
    }

    return status;
}

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                                Functions                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

static status_t mcu_gpio_sanity_check(void)
{
    status_t status = STATUS_SUCCESS;

    CHECK_EQUAL_IF_CUR_STATUS_SUCCESS(status, true, g_mcu_gpio_obj.is_initialized);

    return status;
}

static status_t mcu_gpio_config_check(mcu_gpio_config_t* p_config)
{
    status_t status = STATUS_SUCCESS;

    /* Check if p_config is NULL. */
    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, p_config);

    /* Check if port value in p_config->pin is valid. */
    if(status == STATUS_SUCCESS) {
        if(MCU_GPIO_GET_PORT(p_config->pin) >= MCU_BRIDGE_CFG_GPIO_MAX_PORTS_AVAILABLE) {
            status = STATUS_INVALID_PARAMS;
        }
    }

    /* Check if pin value in p_config->pin is valid. */
    if(status == STATUS_SUCCESS) {
        if(MCU_GPIO_GET_PIN(p_config->pin) >= MCU_BRIDGE_CFG_GPIO_MAX_PINS_PER_PORT) {
            status = STATUS_INVALID_PARAMS;
        }
    }

    /* Check if p_config->pin_dir is valid. */
    if(status == STATUS_SUCCESS) {
        if(!IS_MCU_GPIO_PIN_DIR(p_config->pin_dir)) {
            status = STATUS_INVALID_PARAMS;
        }
    }

    /* Check if p_config->op_pin_initial_val is valid. */
    if(status == STATUS_SUCCESS) {
        if((p_config->pin_dir == MCU_GPIO_PIN_DIR_OUTPUT) && (!IS_MCU_GPIO_PIN_VAL(p_config->op_pin_initial_val))) {
            status = STATUS_INVALID_PARAMS;
        }
    }

    /* Check if p_config->ip_pin_trig_type is valid. */
    if(status == STATUS_SUCCESS) {
        if((p_config->pin_dir == MCU_GPIO_PIN_DIR_INPUT) &&
           (!IS_MCU_GPIO_PIN_INTR_TRIG_TYPE(p_config->ip_pin_trig_type))) {
            status = STATUS_INVALID_PARAMS;
        }
    }

    /* Check if p_config->ip_pin_pull is valid. */
    if(status == STATUS_SUCCESS) {
        if((p_config->pin_dir == MCU_GPIO_PIN_DIR_INPUT) && (!IS_MCU_GPIO_PIN_PULL(p_config->ip_pin_pull))) {
            status = STATUS_INVALID_PARAMS;
        }
    }

    /* No need to check for ISR.
     * By default it will be NULL. Based on need user can register callback.
     */
    return status;
}

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                            Callback Handlers                             |
// |                                                                          |
// +--------------------------------------------------------------------------+

#else
#pragma message "GPIO driver is disabled in mcu_bridge_cfg.h"
#endif /* MCU_BRIDGE_CFG_GPIO_DRIVER_ENABLED */
