#ifndef MCU_CFG_H
#define MCU_CFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* ##################### DRIVERS CONFIG(ENABLE/DISABLE) ##################### */

#define MCU_CFG_GPIO_DRIVER_ENABLED
#define MCU_CFG_TIMER_DRIVER_ENABLED
#define MCU_CFG_ADC_DRIVER_ENABLED

/* ########################### GPIO DRIVER CONFIG ########################### */

/**
 * User defined GPIO index, which can be used in Application.
 * 
 * Example:
 * 
 * #define MCU_CFG_GPIO_IDX_LED1                                            (0U)
 * #define MCU_CFG_GPIO_IDX_LED2                                            (1U)
 * #define MCU_CFG_GPIO_MAX_PINS_TO_USE                                     (2U)
 * 
 * #define MCU_CFG_GPIO_MAX_PORTS_AVAILABLE                                 (2U)
 * #define MCU_CFG_GPIO_MAX_PINS_AVAILABLE                                 (16U)
 * #define MCU_CFG_GPIO_MAX_PINS_TO_USE                                      (2)
 */

/**
 * These are mandatory macros used by MCU Bridge to configure GPIO pins.
 */

/**
 * \def MCU_CFG_GPIO_MAX_PORTS_AVAILABLE
 * \brief Number of GPIO ports available in the target platform.
 */
#define MCU_CFG_GPIO_MAX_PORTS_AVAILABLE                                    (2U)

/**
 * \def MCU_CFG_GPIO_MAX_PINS_AVAILABLE
 * \brief Number of GPIO pins available in the target platform.
 */
#define MCU_CFG_GPIO_MAX_PINS_AVAILABLE                                    (16U)

/**
 * \def MCU_CFG_GPIO_MAX_PINS_TO_USE
 * \brief Number of GPIO pins to be used in the target platform.
 */
#define MCU_CFG_GPIO_MAX_PINS_TO_USE                                         (2)

/* ######################### TIMER DRIVER CONFIG ############################ */

/* ########################## ADC DRIVER CONFIG ############################# */

#ifdef __cplusplus
}
#endif

#endif /* MCU_CFG_H */
