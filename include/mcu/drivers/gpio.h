#ifndef GPIO_H
#define GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <mcu_cfg.h>

/* Exported types ------------------------------------------------------------*/

typedef enum GPIO_PinDir_et_ {
    GPIO_PIN_INPUT = 0,
    GPIO_PIN_OUTPUT
} GPIO_PinDir_et;

typedef enum GPIO_PinVal_et_ {
    GPIO_PIN_LOW = 0,
    GPIO_PIN_HIGH
} GPIO_PinVal_et;

typedef enum GPIO_PortIdx_et_ {
    GPIO_PORT0 = 0,
    GPIO_PORT1,
    GPIO_PORT2,
    GPIO_PORT3,
    GPIO_PORT4,
} GPIO_PortIdx_et;

/* clang-format off */
typedef enum GPIO_PinIdx_et_
{
  P_A0 = GPIO_PIN_PER_PORT * GPIO_PORT0, P_A1, P_A2, P_A3, P_A4, P_A5, P_A6, P_A7, P_A8, P_A9, P_A10, P_A11, P_A12, P_A13, P_A14, P_A15,
  P_B0 = GPIO_PIN_PER_PORT * GPIO_PORT1, P_B1, P_B2, P_B3, P_B4, P_B5, P_B6, P_B7, P_B8, P_B9, P_B10, P_B11, P_B12, P_B13, P_B14, P_B15,
  P_C0 = GPIO_PIN_PER_PORT * GPIO_PORT2, P_C1, P_C2, P_C3, P_C4, P_C5, P_C6, P_C7, P_C8, P_C9, P_C10, P_C11, P_C12, P_C13, P_C14, P_C15,
  P_D0 = GPIO_PIN_PER_PORT * GPIO_PORT3, P_D1, P_D2, P_D3, P_D4, P_D5, P_D6, P_D7, P_D8, P_D9, P_D10, P_D11, P_D12, P_D13, P_D14, P_D15,
  P_E0 = GPIO_PIN_PER_PORT * GPIO_PORT4, P_E1, P_E2, P_E3, P_E4, P_E5, P_E6, P_E7, P_E8, P_E9, P_E10, P_E11, P_E12, P_E13, P_E14, P_E15,
  P_NC = 0xff
} GPIO_PinIdx_et;
/* clang-format on */

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define GPIO_WHICH_PORT(pinId) ((pinId) / GPIO_PIN_PER_PORT)
#define GPIO_WHICH_PIN(pinId)  ((pinId) % GPIO_PIN_PER_PORT)

/* Exported functions ------------------------------------------------------- */
status_et GPIO_SetPinDirection(GPIO_PinIdx_et pin, GPIO_PinDir_et dir);
status_et GPIO_GetPinDirection(GPIO_PinIdx_et pin, GPIO_PinDir_et* pDir);
status_et GPIO_PinWrite(GPIO_PinIdx_et pin, GPIO_PinVal_et val);
status_et GPIO_PinRead(GPIO_PinIdx_et pin, GPIO_PinVal_et* pVal);
status_et GPIO_PinToggle(GPIO_PinIdx_et pin);

#ifdef __cplusplus
}
#endif

#endif /* GPIO_H */