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
