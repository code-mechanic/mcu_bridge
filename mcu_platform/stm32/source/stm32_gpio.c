#include <stm32_gpio.h>
#include <assert.h>
#include <stm32g4xx_hal_gpio.h>

static status_t stm32_gpio_read(void* mcu_gpio_ctx, mcu_gpio_pin_val_t* p_val);

const mcu_gpio_ops_t g_stm32_gpio_ops = {
    .read    = stm32_gpio_read,
    .write   = NULL,
    .set_dir = NULL,
    .get_dir = NULL,
};

status_t stm32_gpio_ctx_init(stm32_gpio_ctx_t* ctx, GPIO_TypeDef* port, uint16_t pin)
{
    status_t status = STATUS_SUCCESS;

    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, ctx);
    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, port);

    ctx->port = port;
    ctx->pin  = pin;

    return status;
}

status_t stm32_gpio_get_gpio_ops(const mcu_gpio_ops_t* p_ops)
{
    status_t status = STATUS_SUCCESS;

    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, p_ops);

    if(status == STATUS_SUCCESS) {
        p_ops = &g_stm32_gpio_ops;
    }

    return status;
}

static status_t stm32_gpio_read(void* mcu_gpio_ctx, mcu_gpio_pin_val_t* p_val)
{
    status_t           status = STATUS_SUCCESS;
    GPIO_PinState      hal_pin_read_status;
    mcu_gpio_pin_val_t read_val;

    stm32_gpio_ctx_t* stm_gpio_ctx = (stm32_gpio_ctx_t*) mcu_gpio_ctx;
    hal_pin_read_status            = HAL_GPIO_ReadPin(stm_gpio_ctx->port, stm_gpio_ctx->pin);
    read_val = (hal_pin_read_status == GPIO_PIN_SET) ? MCU_GPIO_PIN_VAL_HIGH : MCU_GPIO_PIN_VAL_LOW;

    *p_val = read_val;
    return status;
}
