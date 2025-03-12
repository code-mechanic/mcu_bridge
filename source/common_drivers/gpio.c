/* Includes ------------------------------------------------------------------*/
#include <gpio.h>
#include <gpio_dispatch.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
static bool_et isGPIO_PinIdxValid(GPIO_PinIdx_et pin);
static bool_et isGPIO_PinValValid(GPIO_PinVal_et val);
static bool_et isGPIO_PinDirValid(GPIO_PinDir_et dir);

/* Public functions  ---------------------------------------------------------*/
status_et GPIO_SetPinDirection(GPIO_PinIdx_et pin, GPIO_PinDir_et dir)
{
    status_et ret_val = SUCCESS;

    if(!isGPIO_PinIdxValid(pin) || !isGPIO_PinDirValid(dir)) {
        ret_val = FAILED;
    }

    if(ret_val == SUCCESS) {
        ret_val = GPIO_DispatchSetPinDirection(pin, dir);
    }

    return ret_val;
}

status_et GPIO_GetPinDirection(GPIO_PinIdx_et pin, GPIO_PinDir_et* pDir)
{
    status_et ret_val = SUCCESS;

    if(!isGPIO_PinIdxValid(pin) || pDir == NULL) {
        ret_val = FAILED;
    } else {
        *pDir = GPIO_PIN_INPUT;
    }

    if(ret_val == SUCCESS) {
        ret_val = GPIO_DispatchGetPinDirection(pin, pDir);
    }

    return ret_val;
}

status_et GPIO_PinWrite(GPIO_PinIdx_et pin, GPIO_PinVal_et val)
{
    status_et ret_val = SUCCESS;

    if(!isGPIO_PinIdxValid(pin) || !isGPIO_PinValValid(val)) {
        ret_val = FAILED;
    }

    if(ret_val == SUCCESS) {
        ret_val = GPIO_DispatchPinWrite(pin, val);
    }

    return ret_val;
}

status_et GPIO_PinRead(GPIO_PinIdx_et pin, GPIO_PinVal_et* pVal)
{
    status_et ret_val = SUCCESS;

    if(!isGPIO_PinIdxValid(pin) || pVal == NULL) {
        ret_val = FAILED;
    } else {
        *pVal = GPIO_PIN_LOW;
    }

    if(ret_val == SUCCESS) {
        ret_val = GPIO_DispatchPinRead(pin, pVal);
    }

    return ret_val;
}

status_et GPIO_PinToggle(GPIO_PinIdx_et pin)
{
    status_et ret_val = SUCCESS;

    if(!isGPIO_PinIdxValid(pin)) {
        ret_val = FAILED;
    }

    if(ret_val == SUCCESS) {
        ret_val = GPIO_DispatchPinToggle(pin);
    }

    return ret_val;
}

/* Private functions ---------------------------------------------------------*/
static bool_et isGPIO_PinIdxValid(GPIO_PinIdx_et pin)
{
    bool_et ret_val = FALSE;

    if((pin >= GPIO_PIN_PER_PORT * GPIO_PORT0) && (pin <= (GPIO_PIN_PER_PORT * GPIO_PORT4) + GPIO_PIN_PER_PORT)) {
        ret_val = TRUE;
    }

    return ret_val;
}

static bool_et isGPIO_PinValValid(GPIO_PinVal_et val)
{
    bool_et ret_val = FALSE;

    if((val == GPIO_PIN_LOW) || (val == GPIO_PIN_HIGH)) {
        ret_val = TRUE;
    }

    return ret_val;
}

static bool_et isGPIO_PinDirValid(GPIO_PinDir_et dir)
{
    bool_et ret_val = FALSE;

    if((dir == GPIO_PIN_INPUT) || (dir == GPIO_PIN_OUTPUT)) {
        ret_val = TRUE;
    }

    return ret_val;
}
