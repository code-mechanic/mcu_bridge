#ifndef GPIO_DISPATCH_H
#define GPIO_DISPATCH_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <gpio.h>

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
status_et GPIO_DispatchSetPinDirection(GPIO_PinIdx_et pin, GPIO_PinDir_et dir);
status_et GPIO_DispatchGetPinDirection(GPIO_PinIdx_et pin, GPIO_PinDir_et* pDir);
status_et GPIO_DispatchPinWrite(GPIO_PinIdx_et pin, GPIO_PinVal_et val);
status_et GPIO_DispatchPinRead(GPIO_PinIdx_et pin, GPIO_PinVal_et* pVal);
status_et GPIO_DispatchPinToggle(GPIO_PinIdx_et pin);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_DISPATCH_H */
