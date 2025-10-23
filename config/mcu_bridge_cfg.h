#ifndef MCU_BRIDGE_CFG_H
#define MCU_BRIDGE_CFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* ##################### DRIVERS CONFIG(ENABLE/DISABLE) ##################### */

#define MCU_BRIDGE_CFG_GPIO_DRIVER_ENABLED
#define MCU_BRIDGE_CFG_TIMER_DRIVER_ENABLED
#define MCU_BRIDGE_CFG_ADC_DRIVER_ENABLED

/* ########################### GPIO DRIVER CONFIG ########################### */

/**
 * \def MCU_BRIDGE_CFG_GPIO_MAX_PORTS_AVAILABLE
 * \brief Number of GPIO ports available in the target platform.
 */
#define MCU_BRIDGE_CFG_GPIO_MAX_PORTS_AVAILABLE                             (1U)

/**
 * \def MCU_BRIDGE_CFG_GPIO_MAX_PINS_PER_PORT
 * \brief Number of GPIO pins per port available in the target platform.
 */
#define MCU_BRIDGE_CFG_GPIO_MAX_PINS_PER_PORT                               (1U)

/**
 * \def MCU_BRIDGE_CFG_GPIO_MAX_PINS_TO_USE
 * \brief Number of GPIO pins to be used in the target platform.
 */
#define MCU_BRIDGE_CFG_GPIO_MAX_PINS_TO_USE                                 (1U)

/* ######################### TIMER DRIVER CONFIG ############################ */

/* ########################## ADC DRIVER CONFIG ############################# */

#ifdef __cplusplus
}
#endif

#endif /* MCU_BRIDGE_CFG_H */
