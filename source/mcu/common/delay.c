/* Includes ------------------------------------------------------------------*/
#include <delay.h>
#include <xc.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define _XTAL_FREQ (F_CPU)

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Public functions  ---------------------------------------------------------*/
void DelayMs(uint32_t delayMs)
{
    while(delayMs) {
        __delay_ms(1);
        delayMs -= 1;
    }
}

void DelayUs(uint32_t delayUs)
{
    while(delayUs) {
        __delay_us(1);
        delayUs -= 1;
    }
}

/* Private functions ---------------------------------------------------------*/