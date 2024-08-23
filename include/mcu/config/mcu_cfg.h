#ifndef MCU_CFG_H
#define MCU_CFG_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <common.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/

#define F_CPU                                                       (16000000UL)

#define MCU_GPIO_DRIVER                                                  ENABLE 

#define IS_DRIVER_ENABLE(module)               (MCU_##module##_DRIVER == ENABLE)

/* Exported functions ------------------------------------------------------- */
#if IS_DRIVER_ENABLE(GPIO)

#define GPIO_PIN_PER_PORT                                                   (8U)

#endif

#ifdef __cplusplus
}
#endif

#endif /* MCU_CFG_H */

