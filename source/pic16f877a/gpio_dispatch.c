/* Includes ------------------------------------------------------------------*/
#include <pic16f877a.h>
#include <gpio_dispatch.h>
#include <regctrl.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static volatile uint8_t* GPIO_getDirectionReg(GPIO_PinIdx_et pin);
static volatile uint8_t* GPIO_getPortReg(GPIO_PinIdx_et pin);

/* Public functions  ---------------------------------------------------------*/
status_et GPIO_DispatchSetPinDirection(GPIO_PinIdx_et pin, GPIO_PinDir_et dir)
{
    status_et retVal = SUCCESS;
    volatile uint8_t  *directionReg = NULL;

    directionReg = GPIO_getDirectionReg(pin);

    /**
     * In PIC16F877A,
     * Input  = 1
     * Output = 0
     */
    if(dir == GPIO_PIN_INPUT) {
        dir = 1U;
    } else if(dir == GPIO_PIN_OUTPUT) {
        dir = 0U;
    }

    if(directionReg) {
        BIT_Write(*directionReg, GPIO_WHICH_PIN(pin), dir);
    } else {
        retVal = FAILED;
    }

    return retVal;
}

status_et GPIO_DispatchGetPinDirection(GPIO_PinIdx_et pin, GPIO_PinDir_et* pDir)
{
    status_et retVal = SUCCESS;
    volatile uint8_t *directionReg = NULL;
    uint8_t directionRegVal;

    directionReg = GPIO_getDirectionReg(pin);

    if(directionReg)
    {
        directionRegVal = BIT_Read(*directionReg, GPIO_WHICH_PIN(pin));
    } else {
        retVal = FAILED;
    }

    if(retVal == SUCCESS)
    {
        /**
         * In PIC16F877A,
         * Input  = 1
         * Output = 0
         */
        if(directionRegVal == 0) {
            *pDir = GPIO_PIN_OUTPUT;
        } else if(directionRegVal == 1) {
            *pDir = GPIO_PIN_INPUT;
        }
    }

    return retVal;
}

status_et GPIO_DispatchPinWrite(GPIO_PinIdx_et pin, GPIO_PinVal_et val)
{
    status_et retVal = SUCCESS;
    volatile uint8_t *dataOutReg = NULL;

    dataOutReg = GPIO_getPortReg(pin);

    if(dataOutReg) {
        BIT_Write(*dataOutReg, GPIO_WHICH_PIN(pin), val);
    } else {
        retVal = FAILED;
    }

    return retVal;
}

status_et GPIO_DispatchPinRead(GPIO_PinIdx_et pin, GPIO_PinVal_et* pVal)
{
    status_et retVal = SUCCESS;
    volatile uint8_t *dataOutReg = NULL;
    uint8_t dataOutRegVal;
    
    dataOutReg = GPIO_getPortReg(pin);
    
    if(dataOutReg) {
        dataOutRegVal = BIT_Read(*dataOutReg, GPIO_WHICH_PIN(pin));
    } else {
        retVal = FAILED;
    }

    if(retVal == SUCCESS) {
        if(dataOutRegVal == 1U) {
            *pVal = GPIO_PIN_HIGH;
        } else if (dataOutRegVal == 0U) {
            *pVal = GPIO_PIN_LOW;
        }
    }

    return retVal;
}

status_et GPIO_DispatchPinToggle(GPIO_PinIdx_et pin)
{
    status_et retVal = SUCCESS;
    volatile uint8_t *dataOutReg = NULL;
    
    dataOutReg = GPIO_getPortReg(pin);
    
    if(dataOutReg) {
        BIT_Toggle(*dataOutReg, GPIO_WHICH_PIN(pin));
    } else {
        retVal = FAILED;
    }

    return retVal;
}

/* Private functions ---------------------------------------------------------*/
static volatile uint8_t* GPIO_getDirectionReg(GPIO_PinIdx_et pin)
{
    volatile uint8_t *directionReg = NULL;

    switch(GPIO_WHICH_PORT(pin))
    {
#if defined(TRISA)
        case 0:
        directionReg = (uint8_t*)&TRISA;
        break;
#endif

#if defined(TRISB)
        case 1:
        directionReg = (uint8_t*)&TRISB;
        break;
#endif
        
#if defined(TRISC)
        case 2:
        directionReg = (uint8_t*)&TRISC;
        break;
#endif
        
#if defined(TRISD)
        case 3:
        directionReg = (uint8_t*)&TRISD;
        break;
#endif

#if defined(TRISE)
        case 4:
        directionReg = (uint8_t*)&TRISE;
        break;
#endif

        default:
        break;
    }

    return directionReg;
}

static volatile uint8_t* GPIO_getPortReg(GPIO_PinIdx_et pin)
{
    volatile uint8_t *dataOutReg = NULL;

    switch(GPIO_WHICH_PORT(pin))
    {
#if defined(PORTA)
        case 0:
        dataOutReg = (uint8_t*)&PORTA;
        break;
#endif

#if defined(PORTB)
        case 1:
        dataOutReg = (uint8_t*)&PORTB;
        break;
#endif
        
#if defined(PORTC)
        case 2:
        dataOutReg = (uint8_t*)&PORTC;
        break;
#endif
        
#if defined(PORTD)
        case 3:
        dataOutReg = (uint8_t*)&PORTD;
        break;
#endif

#if defined(PORTE)
        case 4:
        dataOutReg = (uint8_t*)&PORTE;
        break;
#endif

        default:
        break;
    }

    return dataOutReg;
}