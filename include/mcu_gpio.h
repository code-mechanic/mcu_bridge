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

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                                 Typedefs                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

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
 * \brief GPIO operations
 */
typedef struct mcu_gpio_ops_t_ {
    /** \brief GPIO read operation */
    status_t (*read)(void* mcu_gpio_ctx, mcu_gpio_pin_val_t* p_val);
    /** \brief GPIO write operation */
    status_t (*write)(void* mcu_gpio_ctx, mcu_gpio_pin_val_t val);
    /** \brief GPIO set direction operation */
    status_t (*set_dir)(void* mcu_gpio_ctx, mcu_gpio_pin_dir_t dir);
    /** \brief GPIO get direction operation */
    status_t (*get_dir)(void* mcu_gpio_ctx, mcu_gpio_pin_dir_t* p_dir);
} mcu_gpio_ops_t;

/**
 * \brief Opaque handle for MCU-agnostic GPIO driver
 *
 * This type defines an **opaque handle** to represent a GPIO instance
 * in a hardware-independent way. The actual definition of the structure
 * is hidden from the application code, so the internal implementation
 * can vary between different MCUs without affecting user code.
 *
 * The handle is used to:
 *   - Identify a specific GPIO pin or port in the driver APIs
 *   - Maintain MCU-specific context (register addresses, configurations, etc.)
 *   - Enable type safety and encapsulation, preventing the application
 *     from directly manipulating low-level MCU registers
 *
 * This allows the GPIO driver to be portable across multiple MCU families
 * while keeping the application code consistent.
 */
typedef struct mcu_gpio_handle_t_ mcu_gpio_handle_t;

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                                Functions                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

/**
 * \name GPIO Initialization functions
 *
 *  @{
 */

/**
 * \brief Initialize a GPIO handle.
 *
 * Initialize a GPIO handle with the given MCU specific ops and context.
 *
 * \param[in] p_gpio_handle  Pointer to the GPIO handle to be initialized.
 * \param[in] p_ops  Pointer to the MCU specific GPIO operations.
 * \param[in] mcu_gpio_ctx  Pointer to the MCU specific GPIO context.
 *
 * \return STATUS_SUCCESS if the handle is initialized successfully.
 */
status_t mcu_gpio_init_handle(mcu_gpio_handle_t* p_gpio_handle, mcu_gpio_ops_t* p_ops, void* mcu_gpio_ctx);

/** @} */

/**
 * \name GPIO run-time functions
 *
 *  @{
 */

/**
 * \brief Reads the current value of a GPIO pin.
 *
 * Reads the current value of a GPIO pin. The value will be stored in the
 * p_val parameter.
 *
 * \param[in] p_gpio_handle  Pointer to the GPIO handle.
 * \param[out] p_val  Pointer to the value which will store the current pin value.
 *
 * \return STATUS_SUCCESS if the operation is successful.
 */
status_t mcu_gpio_read(mcu_gpio_handle_t* p_gpio_handle, mcu_gpio_pin_val_t* p_val);

/**
 * \brief Writes a value to a GPIO pin.
 *
 * Writes a value to a GPIO pin specified by the given handle.
 *
 * \param[in] p_gpio_handle  Pointer to the GPIO handle.
 * \param[in] val  Value to be written to the GPIO pin.
 *
 * \return STATUS_SUCCESS if the operation is successful.
 */
status_t mcu_gpio_write(mcu_gpio_handle_t* p_gpio_handle, mcu_gpio_pin_val_t val);

/**
 * @brief Sets the direction of a GPIO pin.
 *
 * Sets the direction of a GPIO pin specified by the given handle.
 *
 * @param[in] p_gpio_handle Pointer to the GPIO handle.
 * @param[in] dir Direction to be set.
 *
 * @return STATUS_SUCCESS if the operation is successful.
 */
status_t mcu_gpio_set_dir(mcu_gpio_handle_t* p_gpio_handle, mcu_gpio_pin_dir_t dir);

/**
 * @brief Retrieves the current direction of a GPIO pin.
 *
 * Retrieves the current direction of a GPIO pin specified by the given handle.
 *
 * @param[in] p_gpio_handle  Pointer to the GPIO handle.
 * @param[out] p_dir  Pointer to the variable which will store the current direction of the GPIO pin.
 *
 * @return STATUS_SUCCESS if the operation is successful.
 */
status_t mcu_gpio_get_dir(mcu_gpio_handle_t* p_gpio_handle, mcu_gpio_pin_dir_t* p_dir);
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* MCU_GPIO_H */

/** @} */
