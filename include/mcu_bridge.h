/**
 * \defgroup MCU_BRIDGE_INIT MCU Bridge Initialization API
 * \ingroup MCU_BRIDGE
 *
 * @{
 */

/**
 * \file mcu_bridge.h
 * \brief  MCU Bridge initialization API. Application need to include this file and call \ref mcu_bridge_init() before
 * using any other APIs.
 */

#ifndef MCU_BRIDGE_H
#define MCU_BRIDGE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <common/status.h>
#include <mcu_bridge_cfg.h>

#ifdef STM32_HAL_HEADER
/* STM32 MCU header. Macro will be created as a part of CMakeLists.txt */
#include STM32_HAL_HEADER
#endif

#ifdef MCU_BRIDGE_CFG_GPIO_DRIVER_ENABLED
#include <mcu_drivers/mcu_gpio.h>
#endif

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

/** \brief MCU Bridge initialization parameters */
typedef struct mcu_bridge_init_param_t_ {
    /** \brief Pointer to the user defined clock configuration function
     *  \note For STM32 MCU, HAL clock configuration can be overriden by this function
     */
    status_t (*mcu_clock_config)(void);
} mcu_bridge_init_param_t;

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                                Functions                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

/**
 * \brief Initialize MCU Bridge.
 *
 * \param[in] p_init_param Pointer to the MCU Bridge initialization parameters.
 *
 * \return STATUS_SUCCESS if the initialization was successful.
 */
status_t mcu_bridge_init(mcu_bridge_init_param_t* p_init_param);

/**
 * \brief Delay for a given number of milliseconds
 *
 * \param[in] delay_ms Number of milliseconds to delay
 */
void mcu_bridge_delay_ms(uint32_t delay_ms);

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                          Static inline Functions                         |
// |                                                                          |
// +--------------------------------------------------------------------------+

#ifdef __cplusplus
}
#endif

#endif /* MCU_BRIDGE_H */

/** @} */

/**
 * \defgroup MCU_BRIDGE MCU Bridge API
 * \brief
 */
