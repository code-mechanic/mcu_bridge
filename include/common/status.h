#ifndef STATUS_H
#define STATUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

/**
 *  \anchor status_t
 *  \name Type status_t, common status codes used by all modules
 *
 *  @{
 */
typedef enum status_t_ {
    STATUS_SUCCESS                 = 0,
    STATUS_FAILURE                 = 1,
    STATUS_INVALID_PARAMS          = 2,
    STATUS_UNSUPPORTED_FEATURE     = 3,
    STATUS_MCU_INIT_DRIVER_FAILURE = 4,
    STATUS_MCU_GPIO_NOT_CONFIGURED = 5,
} status_t;

/** @} */

#define EXEC_FUNC_IF_CUR_STATUS_SUCCESS(status, function)        \
    do {                                                         \
        status = (status == STATUS_SUCCESS) ? function : status; \
    } while(0);

#define CHECK_NULL_IF_CUR_STATUS_SUCCESS(cur_status, ptr) \
    do {                                                  \
        if((cur_status) == STATUS_SUCCESS) {              \
            if((ptr) == NULL) {                           \
                cur_status = STATUS_INVALID_PARAMS;       \
            }                                             \
        }                                                 \
    } while(0);

#define CHECK_EQUAL_IF_CUR_STATUS_SUCCESS(cur_status, expected, actual) \
    do {                                                                \
        if((cur_status) == STATUS_SUCCESS) {                            \
            if((expected) != (actual)) {                                \
                cur_status = STATUS_FAILURE;                            \
            }                                                           \
        }                                                               \
    } while(0);

#ifdef __cplusplus
}
#endif

#endif /* STATUS_H */
