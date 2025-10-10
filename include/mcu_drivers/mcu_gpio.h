/**
 * \defgroup MCU_BRIDGE_GPIO MCU bridge GPIO API
 * \ingroup MCU_BRIDGE_DRIVERS
 *
 * MCU GPIO abstraction header for portable GPIO operations.
 * Defines types, function prototypes, and interface structures for
 * reading, writing, and configuring GPIO pins in a hardware-independent manner,
 * following the MCU bridge coding guidelines.
 *
 * Intended for use as a template for implementing GPIO drivers across
 * different microcontroller platforms.
 *
 * @{
 */

/**
 * \file mcu_gpio.h
 * \brief MCU GPIO API
 */

#ifndef MCU_GPIO_H
#define MCU_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <status.h>

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                          Definitions and Macros                          |
// |                                                                          |
// +--------------------------------------------------------------------------+

/** \brief Get the port number from a GPIO pin value. \ref mcu_gpio_pin_t */
#define MCU_GPIO_GET_PORT(pin) ((pin) >> 8U)

/** \brief Get the pin number from a GPIO pin value. \ref mcu_gpio_pin_t */
#define MCU_GPIO_GET_PIN(pin) ((pin) & 0xFFU)

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                                 Typedefs                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

/**
 * \brief GPIO pin number. \ref mcu_gpio_create_pin to create this value
 */
typedef uint16_t mcu_gpio_pin_t;

/**
 * \brief GPIO Pin value
 */
typedef enum mcu_gpio_pin_val_t_ {
    /** \brief GPIO pin is at logic low */
    MCU_GPIO_PIN_VAL_LOW = 0u,
    /** \brief GPIO pin is at logic high */
    MCU_GPIO_PIN_VAL_HIGH = 1u
} mcu_gpio_pin_val_t;

/**
 * \brief GPIO Pin Direction
 */
typedef enum mcu_gpio_pin_dir_t_ {
    /** \brief GPIO pin direction Input */
    MCU_GPIO_PIN_DIR_INPUT = 0u,
    /** \brief GPIO pin direction Output */
    MCU_GPIO_PIN_DIR_OUTPUT = 1u
} mcu_gpio_pin_dir_t;

/**
 * \brief GPIO Pin Pull Type
 */
typedef enum mcu_gpio_pin_pull_t_ {
    /** \brief GPIO pin pull invalid. Use this if MCU does not support pull */
    MCU_GPIO_PIN_PULL_INVALID,
    /** \brief GPIO pin pull none */
    MCU_GPIO_PIN_PULL_NONE,
    /** \brief GPIO pin pull up */
    MCU_GPIO_PIN_PULL_UP,
    /** \brief GPIO pin pull down */
    MCU_GPIO_PIN_PULL_DOWN,
    /** \brief Maximum GPIO pin pull type */
    MCU_GPIO_PIN_PULL_MAX
} mcu_gpio_pin_pull_t;

/**
 * \brief GPIO Pin Speed
 */
typedef enum mcu_gpio_pin_speed_t_ {
    /** \brief GPIO pin speed invalid. Use this if MCU does not support speed */
    MCU_GPIO_PIN_SPEED_INVALID,
    /** \brief GPIO pin speed low */
    MCU_GPIO_PIN_SPEED_LOW,
    /** \brief GPIO pin speed medium */
    MCU_GPIO_PIN_SPEED_MEDIUM,
    /** \brief GPIO pin speed high */
    MCU_GPIO_PIN_SPEED_HIGH,
    /** \brief GPIO pin speed very high */
    MCU_GPIO_PIN_SPEED_VERY_HIGH,
    /** \brief Maximum GPIO pin speed */
    MCU_GPIO_PIN_SPEED_MAX,
} mcu_gpio_pin_speed_t;

/**
 * \brief GPIO Input Trigger Type
 *
 * This specifies the interrupt trigger condition for an input GPIO pin.
 */
typedef enum mcu_gpio_intr_trig_type_t_ {
    /** \brief Invalid interrupt trigger type. Use this if MCU does not support interrupts */
    MCU_GPIO_PIN_INTR_TRIG_TYPE_INVALID,
    /** \brief No interrupt triggered */
    MCU_GPIO_PIN_INTR_TRIG_TYPE_NONE,
    /** \brief Interrupt triggered with a rising edge on the input pin */
    MCU_GPIO_PIN_INTR_TRIG_TYPE_RISE,
    /** \brief Interrupt triggered with a falling edge on the input pin */
    MCU_GPIO_PIN_INTR_TRIG_TYPE_FALL,
    /** \brief Interrupt triggered with both rising edge and falling edge */
    MCU_GPIO_PIN_INTR_TRIG_TYPE_RISE_FALL,
    /** \brief Maximum interrupt trigger type */
    MCU_GPIO_PIN_INTR_TRIG_TYPE_MAX
} mcu_gpio_intr_trig_type_t;

/**
 * \brief Function prototype of the gpio interrupt trigger callback function
 */
typedef void (*mcu_gpio_intr_callback_t)(void*);

/**
 * \brief Function prototype of the user defined gpio configuration callback function.
 *
 * As a part of \ref mcu_gpio_config_t, the user can specify a callback function which
 * will be called before GPIO configuration is going to be done.
 *
 * This will be useful for any initialization that needs to be done which are not
 * taken care of by the \ref mcu_gpio_config.
 */
typedef void (*mcu_gpio_config_callback_t)(void);

/**
 * \brief GPIO register callback parameters
 */
typedef struct mcu_gpio_register_callback_params_t_ {
    /** \brief callback function pointer */
    mcu_gpio_intr_callback_t isr;
    /** \brief callback function argument */
    void* p_arg;
} mcu_gpio_register_callback_params_t;

/**
 * \brief GPIO configuration
 */
typedef struct mcu_gpio_config_t_ {
    /* Pin configurations */

    /** \brief MCU specific GPIO pin number. \ref mcu_gpio_create_pin */
    mcu_gpio_pin_t pin;
    /** \brief GPIO pin direction. See \ref mcu_gpio_pin_dir_t */
    mcu_gpio_pin_dir_t pin_dir;
    /** \brief GPIO output pin initial value.
     * This is only valid if \ref mcu_gpio_config_t::pin_dir is set to \ref MCU_GPIO_PIN_DIR_OUTPUT */
    mcu_gpio_pin_val_t op_pin_initial_val;
    /** \brief GPIO output pin speed.
     * This is only valid if \ref mcu_gpio_config_t::pin_dir is set to \ref MCU_GPIO_PIN_DIR_OUTPUT */
    mcu_gpio_pin_speed_t op_pin_speed;
    /** \brief GPIO input pin pull type.
     * This is only valid if \ref mcu_gpio_config_t::pin_dir is set to \ref MCU_GPIO_PIN_DIR_INPUT */
    mcu_gpio_pin_pull_t ip_pin_pull;

    /* Interrupt configurations */

    /** \brief GPIO input pin trigger type.
     * This is only valid if \ref mcu_gpio_config_t::pin_dir is set to \ref MCU_GPIO_PIN_DIR_INPUT */
    mcu_gpio_intr_trig_type_t ip_pin_trig_type;
    /** \brief GPIO input pin interrupt callback parameters.
     * This is only valid if \ref mcu_gpio_config_t::pin_dir is set to \ref MCU_GPIO_PIN_DIR_INPUT */
    mcu_gpio_register_callback_params_t isr_param;

    /* Callback function */
    /** \brief GPIO configuration callback function */
    mcu_gpio_config_callback_t config_callback;
} mcu_gpio_config_t;

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                                Functions                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

/**
 * \name GPIO Initialization API
 *
 *  @{
 */

/**
 * \brief Initialize the MCU GPIO bridge.
 *
 * \note This API is called within \ref mcu_bridge_init() and need not be called by application directly
 *
 * \return STATUS_SUCCESS if the operation is successful.
 */
status_t mcu_gpio_init(void);

/**
 * \brief Uninitialize the MCU GPIO bridge.
 *
 * \return STATUS_SUCCESS if the uninitialization was successful.
 */
status_t mcu_gpio_deinit(void);

/** @} */

/**
 * \name GPIO Configuration API
 *
 *  @{
 */

/**
 * \brief Sets default values to a GPIO configuration structure.
 *
 * \param[in] gpio_idx: GPIO index. Index should not exceed \c MCU_CFG_GPIO_MAX_PINS_TO_USE in mcu_config.h and \ref
 * mcu_gpio_create_pin to create a GPIO pin.
 * \param[in] p_config: Pointer to a GPIO configuration structure.
 *
 * \return Status of the operation.
 *
 * This function sets default values to a GPIO configuration structure.
 * It sets pin to MCU_GPIO_CONFIG_DEFAULT_PIN, pin direction to MCU_GPIO_CONFIG_DEFAULT_PIN_DIR,
 * output pin initial value to MCU_GPIO_CONFIG_DEFAULT_PIN_VAL, output pin speed to MCU_GPIO_CONFIG_DEFAULT_PIN_SPEED,
 * input pin pull to MCU_GPIO_CONFIG_DEFAULT_PIN_PULL, input pin trigger type to MCU_GPIO_CONFIG_DEFAULT_PIN_TRIG_TYPE,
 * and ISR callback parameters to NULL.
 */
status_t mcu_gpio_config_set_default(uint32_t gpio_idx, mcu_gpio_config_t* p_config);

/**
 * \brief Configure a GPIO pin with a given configuration.
 *
 * \note For STM32 MCU, this will not configure the Alternate function for the GPIO pin. User need to use
 * \ref mcu_gpio_config_callback_t to configure the Alternate function.
 *
 * \param[in] gpio_idx The index of the GPIO pin to be configured. Index should not exceed \c
 * MCU_CFG_GPIO_MAX_PINS_TO_USE in mcu_cfg.h and \ref mcu_gpio_create_pin to create a GPIO pin. \param[in] p_config The
 * configuration to be applied to the GPIO pin. \ref mcu_gpio_config_t
 *
 * \return STATUS_SUCCESS if the configuration was successful.
 */
status_t mcu_gpio_config(uint32_t gpio_idx, mcu_gpio_config_t* p_config);

/** @} */

/**
 * \name GPIO Functional API
 *
 *  @{
 */

/**
 * \brief Reads the value of a GPIO pin.
 *
 * \param[in] gpio_idx The index of the GPIO pin to be read. Index should not exceed \c MCU_CFG_GPIO_MAX_PINS_TO_USE in
 * mcu_cfg.h and \ref mcu_gpio_create_pin to create a GPIO pin. \param[out] p_val The value of the GPIO pin to be
 * stored.
 *
 * \return STATUS_SUCCESS if the read operation was successful.
 */
status_t mcu_gpio_read(uint32_t gpio_idx, mcu_gpio_pin_val_t* p_val);

/**
 * \brief Writes a value to a GPIO pin.
 *
 * \param[in] gpio_idx The index of the GPIO pin to be written. Index should not exceed \c
 * MCU_CFG_GPIO_MAX_PINS_TO_USE in mcu_cfg.h and \ref mcu_gpio_create_pin to create a GPIO pin.
 * \param[in] val The value to be written to the GPIO pin.
 *
 * \return STATUS_SUCCESS if the write operation was successful.
 */
status_t mcu_gpio_write(uint32_t gpio_idx, mcu_gpio_pin_val_t val);

/**
 * \brief Toggles the value of a GPIO pin.
 *
 * \param[in] gpio_idx The index of the GPIO pin to be toggled. Index should not exceed \c
 * MCU_CFG_GPIO_MAX_PINS_TO_USE in mcu_cfg.h and \ref mcu_gpio_create_pin to create a GPIO pin.
 *
 * \return STATUS_SUCCESS if the toggle operation was successful.
 */
status_t mcu_gpio_toggle(uint32_t gpio_idx);

/**
 * \brief Gets the direction of a GPIO pin.
 *
 * \param[in] gpio_idx The index of the GPIO pin to be read. Index should not exceed \c MCU_CFG_GPIO_MAX_PINS_TO_USE in
 * mcu_cfg.h and \ref mcu_gpio_create_pin to create a GPIO pin. \param[in] dir The direction of the GPIO pin to be
 * stored.
 *
 * \return STATUS_SUCCESS if the read operation was successful.
 */
status_t mcu_gpio_set_dir(uint32_t gpio_idx, mcu_gpio_pin_dir_t dir);

/**
 * \brief Gets the direction of a GPIO pin.
 *
 * \param[in] gpio_idx The index of the GPIO pin to be read. Index should not exceed \c MCU_CFG_GPIO_MAX_PINS_TO_USE in
 * mcu_cfg.h and \ref mcu_gpio_create_pin to create a GPIO pin. \param[out] p_dir The direction of the GPIO pin to be
 * stored.
 *
 * \return STATUS_SUCCESS if the read operation was successful.
 */
status_t mcu_gpio_get_dir(uint32_t gpio_idx, mcu_gpio_pin_dir_t* p_dir);

/** @} */

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                          Static inline Functions                         |
// |                                                                          |
// +--------------------------------------------------------------------------+

/**
 * \brief Creates a GPIO pin value from a port and pin number
 *
 * This function creates a GPIO pin value by combining the port and pin
 * numbers. The port number is shifted 8 bits to the left and then
 * bitwise ORed with the pin number.
 *
 * \param[in] port Port number.
 *             Example for port A, use 0; for port B, use 1, etc.
 *             Port number must be less than \c MCU_CFG_GPIO_MAX_PORTS_AVAILABLE in mcu_cfg.h.
 * \param[in] pin Pin number.
 *            Example for pin 0, use 0; for pin 1, use 1, etc.
 *            Pin number must be less than \c MCU_CFG_GPIO_MAX_PINS_AVAILABLE in mcu_cfg.h.
 * \return GPIO pin value
 */
static inline mcu_gpio_pin_t mcu_gpio_create_pin(uint8_t port, uint8_t pin)
{
    return ((mcu_gpio_pin_t) port << 8U) | (mcu_gpio_pin_t) pin;
}

#ifdef __cplusplus
}
#endif

#endif /* MCU_GPIO_H */

/** @} */
