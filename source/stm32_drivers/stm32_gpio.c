#include <mcu_bridge_cfg.h>
#ifdef MCU_BRIDGE_CFG_GPIO_DRIVER_ENABLED

#include <mcu_gpio_bridge.h>
#include <common/utils.h>
/* STM32 MCU header. Macro will be created as a part of CMakeLists.txt */
#include STM32_CMSIS_DEVICE_HEADER
#include STM32_HAL_GPIO_HEADER
#include STM32_HAL_RCC_HEADER

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

typedef struct stm32_gpio_ctx_t_ {
    GPIO_TypeDef*    port;   /**< GPIO Port */
    GPIO_InitTypeDef config; /**< GPIO Init structure */
} stm32_gpio_ctx_t;

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                           Function Prototypes                            |
// |                                                                          |
// +--------------------------------------------------------------------------+

static inline GPIO_TypeDef* stm32_gpio_get_port_base(uint8_t port);
static void                 stm32_gpio_clk_enable(GPIO_TypeDef* p_port);
static uint32_t             stm32_gpio_get_mode(mcu_gpio_pin_dir_t pin_dir, mcu_gpio_intr_trig_type_t trig_type);
static uint32_t             stm32_gpio_get_pull(mcu_gpio_pin_pull_t pull);
static uint32_t             stm32_gpio_get_speed(mcu_gpio_pin_speed_t speed);
static bool                 is_stm32_gpio_configured(uint32_t gpio_idx);

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                          Variable Declarations                           |
// |                                                                          |
// +--------------------------------------------------------------------------+

static stm32_gpio_ctx_t g_stm32_gpio_ctx[MCU_BRIDGE_CFG_GPIO_MAX_PINS_TO_USE];
static uint32_t g_stm32_gpio_config_tracker[MB_BIT_UINT32_ARRAY_CALC_TOTAL_SIZE(MCU_BRIDGE_CFG_GPIO_MAX_PINS_TO_USE)];

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                                Functions                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

status_t mcu_gpio_bridge_init(void)
{
    status_t status = STATUS_SUCCESS;

    for(uint32_t gpio_idx = 0; gpio_idx < MCU_BRIDGE_CFG_GPIO_MAX_PINS_TO_USE; gpio_idx++) {
        MB_ZERO_STRUCT(g_stm32_gpio_ctx[gpio_idx]);
        MB_BIT_UINT32_ARRAY_CLEAR_BIT(g_stm32_gpio_config_tracker, gpio_idx);
    }

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
    status_t status                 = STATUS_SUCCESS;
    g_stm32_gpio_ctx[gpio_idx].port = stm32_gpio_get_port_base(MCU_GPIO_GET_PORT(p_config->pin));

    /* Check if port base address is NULL. */
    if(g_stm32_gpio_ctx[gpio_idx].port == NULL) {
        status = STATUS_UNSUPPORTED_FEATURE;
    }

    if(status == STATUS_SUCCESS) {
        stm32_gpio_clk_enable(g_stm32_gpio_ctx[gpio_idx].port);
        g_stm32_gpio_ctx[gpio_idx].config.Pin   = MB_BIT_MASK(p_config->pin);
        g_stm32_gpio_ctx[gpio_idx].config.Mode  = stm32_gpio_get_mode(p_config->pin_dir, p_config->ip_pin_trig_type);
        g_stm32_gpio_ctx[gpio_idx].config.Pull  = stm32_gpio_get_pull(p_config->ip_pin_pull);
        g_stm32_gpio_ctx[gpio_idx].config.Speed = stm32_gpio_get_speed(p_config->op_pin_speed);

        /* Alternate functions are expected to be set by user using callback, if required */
        if(p_config->config_callback) {
            p_config->config_callback();
        }

        HAL_GPIO_Init(g_stm32_gpio_ctx[gpio_idx].port, &g_stm32_gpio_ctx[gpio_idx].config);
        MB_BIT_UINT32_ARRAY_SET_BIT(g_stm32_gpio_config_tracker, gpio_idx);
    }

    return status;
}

status_t mcu_gpio_bridge_read(uint32_t gpio_idx, mcu_gpio_pin_val_t* p_val)
{
    status_t           status = STATUS_SUCCESS;
    GPIO_PinState      hal_pin_read_status;
    mcu_gpio_pin_val_t read_val;

    if(!is_stm32_gpio_configured(gpio_idx)) {
        status = STATUS_MCU_GPIO_NOT_CONFIGURED;
    }

    if(status == STATUS_SUCCESS) {
        /* g_stm32_gpio_ctx[gpio_idx].port: User should properly initialize the port */
        /* g_stm32_gpio_ctx[gpio_idx].pin: HAL APIs has built in check for pins `IS_GPIO_PIN` */

        hal_pin_read_status = HAL_GPIO_ReadPin(g_stm32_gpio_ctx[gpio_idx].port, g_stm32_gpio_ctx[gpio_idx].config.Pin);
        read_val            = (hal_pin_read_status == GPIO_PIN_SET) ? MCU_GPIO_PIN_VAL_HIGH : MCU_GPIO_PIN_VAL_LOW;
        *p_val              = read_val;
    }

    return status;
}

status_t mcu_gpio_bridge_write(uint32_t gpio_idx, mcu_gpio_pin_val_t val)
{
    status_t      status            = STATUS_SUCCESS;
    GPIO_PinState hal_pin_write_val = (val == MCU_GPIO_PIN_VAL_HIGH) ? GPIO_PIN_SET : GPIO_PIN_RESET;
    if(!is_stm32_gpio_configured(gpio_idx)) {
        status = STATUS_MCU_GPIO_NOT_CONFIGURED;
    }

    if(status == STATUS_SUCCESS) {
        /* g_stm32_gpio_ctx[gpio_idx].port: User should properly initialize the port */
        /* g_stm32_gpio_ctx[gpio_idx].pin: HAL APIs has built in check for pins `IS_GPIO_PIN` */

        HAL_GPIO_WritePin(g_stm32_gpio_ctx[gpio_idx].port, g_stm32_gpio_ctx[gpio_idx].config.Pin, hal_pin_write_val);
    }
    return status;
}

status_t mcu_gpio_bridge_toggle(uint32_t gpio_idx)
{
    status_t status = STATUS_SUCCESS;

    if(!is_stm32_gpio_configured(gpio_idx)) {
        status = STATUS_MCU_GPIO_NOT_CONFIGURED;
    }

    if(status == STATUS_SUCCESS) {
        /* g_stm32_gpio_ctx[gpio_idx].port: User should properly initialize the port */
        /* g_stm32_gpio_ctx[gpio_idx].pin: HAL APIs has built in check for pins `IS_GPIO_PIN` */

        HAL_GPIO_TogglePin(g_stm32_gpio_ctx[gpio_idx].port, g_stm32_gpio_ctx[gpio_idx].config.Pin);
    }
    return status;
}

status_t mcu_gpio_bridge_set_dir(uint32_t gpio_idx, mcu_gpio_pin_dir_t dir)
{
    status_t status = STATUS_SUCCESS;

    /* In the STM32 HAL there isn't a clean way to set just the pin direction.
     * User's should instead set the pin direction using mcu_gpio_config()
     */
    status = STATUS_UNSUPPORTED_FEATURE;

    return status;
}

status_t mcu_gpio_bridge_get_dir(uint32_t gpio_idx, mcu_gpio_pin_dir_t* p_dir)
{
    status_t status = STATUS_SUCCESS;

    if(!is_stm32_gpio_configured(gpio_idx)) {
        status = STATUS_MCU_GPIO_NOT_CONFIGURED;
    }

    if(status == STATUS_SUCCESS) {
        if(g_stm32_gpio_ctx[gpio_idx].config.Mode == GPIO_MODE_OUTPUT_PP) {
            *p_dir = MCU_GPIO_PIN_DIR_OUTPUT;
        } else {
            *p_dir = MCU_GPIO_PIN_DIR_INPUT;
        }
    }
    return status;
}

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                                Functions                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

static inline GPIO_TypeDef* stm32_gpio_get_port_base(uint8_t port)
{
    switch(port) {
#if defined(GPIOA)
        case 0:
            return GPIOA;
#endif
#if defined(GPIOB)
        case 1:
            return GPIOB;
#endif
#if defined(GPIOC)
        case 2:
            return GPIOC;
#endif
#if defined(GPIOD)
        case 3:
            return GPIOD;
#endif
#if defined(GPIOE)
        case 4:
            return GPIOE;
#endif
#if defined(GPIOF)
        case 5:
            return GPIOF;
#endif
#if defined(GPIOG)
        case 6:
            return GPIOG;
#endif
        default:
            return NULL; // port not supported
    }
}

static void stm32_gpio_clk_enable(GPIO_TypeDef* p_port)
{
    if(GPIOA == p_port) {
        __HAL_RCC_GPIOA_CLK_ENABLE();
    } else if(GPIOB == p_port) {
        __HAL_RCC_GPIOB_CLK_ENABLE();
    } else if(GPIOC == p_port) {
        __HAL_RCC_GPIOC_CLK_ENABLE();
    } else if(GPIOD == p_port) {
        __HAL_RCC_GPIOD_CLK_ENABLE();
    } else if(GPIOE == p_port) {
        __HAL_RCC_GPIOE_CLK_ENABLE();
    } else if(GPIOF == p_port) {
        __HAL_RCC_GPIOF_CLK_ENABLE();
    } else if(GPIOG == p_port) {
        __HAL_RCC_GPIOG_CLK_ENABLE();
    } else {
        /* Port not supported */
    }
}

static uint32_t stm32_gpio_get_mode(mcu_gpio_pin_dir_t pin_dir, mcu_gpio_intr_trig_type_t trig_type)
{
    uint32_t mode = GPIO_MODE_INPUT;

    if(MCU_GPIO_PIN_DIR_OUTPUT == pin_dir) {
        mode = GPIO_MODE_OUTPUT_PP;
    } else {
        switch(trig_type) {
            case MCU_GPIO_PIN_INTR_TRIG_TYPE_NONE:
                mode = GPIO_MODE_INPUT;
                break;

            case MCU_GPIO_PIN_INTR_TRIG_TYPE_RISE:
                mode = GPIO_MODE_IT_RISING;
                break;

            case MCU_GPIO_PIN_INTR_TRIG_TYPE_FALL:
                mode = GPIO_MODE_IT_FALLING;
                break;

            case MCU_GPIO_PIN_INTR_TRIG_TYPE_RISE_FALL:
                mode = GPIO_MODE_IT_RISING_FALLING;
                break;

            default:
                /* Params check already done. So it won't end up here */
                break;
        }
    }

    return mode;
}

static uint32_t stm32_gpio_get_pull(mcu_gpio_pin_pull_t pull)
{
    uint32_t stm32_pull = GPIO_NOPULL;

    if(pull == MCU_GPIO_PIN_PULL_NONE) {
        stm32_pull = GPIO_NOPULL;
    } else if(pull == MCU_GPIO_PIN_PULL_UP) {
        stm32_pull = GPIO_PULLUP;
    } else if(pull == MCU_GPIO_PIN_PULL_DOWN) {
        stm32_pull = GPIO_PULLDOWN;
    } else {
        stm32_pull = GPIO_NOPULL;
    }

    return stm32_pull;
}

static uint32_t stm32_gpio_get_speed(mcu_gpio_pin_speed_t speed)
{
    uint32_t stm32_speed = GPIO_SPEED_FREQ_LOW;

    if(speed == MCU_GPIO_PIN_SPEED_LOW) {
        stm32_speed = GPIO_SPEED_FREQ_LOW;
    } else if(speed == MCU_GPIO_PIN_SPEED_MEDIUM) {
        stm32_speed = GPIO_SPEED_FREQ_MEDIUM;
    } else if(speed == MCU_GPIO_PIN_SPEED_HIGH) {
        stm32_speed = GPIO_SPEED_FREQ_HIGH;
    } else if(speed == MCU_GPIO_PIN_SPEED_VERY_HIGH) {
        stm32_speed = GPIO_SPEED_FREQ_VERY_HIGH;
    } else {
        stm32_speed = GPIO_SPEED_FREQ_LOW;
    }

    return stm32_speed;
}

static inline bool is_stm32_gpio_configured(uint32_t gpio_idx)
{
    return MB_BIT_UINT32_ARRAY_READ_BIT(g_stm32_gpio_config_tracker, gpio_idx);
}

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                            Callback Handlers                             |
// |                                                                          |
// +--------------------------------------------------------------------------+

#endif /* MCU_BRIDGE_CFG_GPIO_DRIVER_ENABLED */
