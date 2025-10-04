#include <mcu_gpio.h>
#include <stdbool.h>

typedef struct mcu_gpio_handle_t_ {
    /* Base operations */
    const mcu_gpio_ops_t* ops;
    /* HAL/MCU specific context */
    void* mcu_gpio_ctx;
    /* Flag which will make sure mcu_gpio_*_ops_t are not NULL. */
    bool is_initialized;
} mcu_gpio_handle_t;

static status_t mcu_gpio_handle_sanity_check(mcu_gpio_handle_t* p_gpio_handle);

status_t mcu_gpio_init_handle(mcu_gpio_handle_t* p_gpio_handle, mcu_gpio_ops_t* p_ops, void* mcu_gpio_ctx)
{
    status_t status = STATUS_SUCCESS;

    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, p_gpio_handle);
    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, p_ops);
    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, mcu_gpio_ctx);

    /** NOTE: MCU specific implementation provide a utility function to user to pass this ops variable */
    p_gpio_handle->ops          = p_ops;
    p_gpio_handle->mcu_gpio_ctx = mcu_gpio_ctx;

    p_gpio_handle->is_initialized = true;

    return status;
}

status_t mcu_gpio_read(mcu_gpio_handle_t* p_gpio_handle, mcu_gpio_pin_val_t* p_val)
{
    status_t status = mcu_gpio_handle_sanity_check(p_gpio_handle);

    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, p_gpio_handle->ops->read);
    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, p_val);

    return p_gpio_handle->ops->read(p_gpio_handle->mcu_gpio_ctx, p_val);
}

status_t mcu_gpio_write(mcu_gpio_handle_t* p_gpio_handle, mcu_gpio_pin_val_t val)
{
    status_t status = mcu_gpio_handle_sanity_check(p_gpio_handle);

    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, p_gpio_handle->ops->write);

    return p_gpio_handle->ops->write(p_gpio_handle->mcu_gpio_ctx, val);
}

status_t mcu_gpio_set_dir(mcu_gpio_handle_t* p_gpio_handle, mcu_gpio_pin_dir_t dir)
{
    status_t status = mcu_gpio_handle_sanity_check(p_gpio_handle);

    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, p_gpio_handle->ops->set_dir);

    return p_gpio_handle->ops->set_dir(p_gpio_handle->mcu_gpio_ctx, dir);
}

status_t mcu_gpio_get_dir(mcu_gpio_handle_t* p_gpio_handle, mcu_gpio_pin_dir_t* p_dir)
{
    status_t status = mcu_gpio_handle_sanity_check(p_gpio_handle);

    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, p_gpio_handle->ops->get_dir);
    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, p_dir);

    return p_gpio_handle->ops->get_dir(p_gpio_handle->mcu_gpio_ctx, p_dir);
}

static status_t mcu_gpio_handle_sanity_check(mcu_gpio_handle_t* p_gpio_handle)
{
    status_t status = STATUS_SUCCESS;

    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, p_gpio_handle);
    CHECK_EQUAL_IF_CUR_STATUS_SUCCESS(status, true, p_gpio_handle->is_initialized);
    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, p_gpio_handle->ops);
    CHECK_NULL_IF_CUR_STATUS_SUCCESS(status, p_gpio_handle->mcu_gpio_ctx);

    return status;
}