#ifndef STATUS_H
#define STATUS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>

#define STATUS_SUCCESS             (0x00000000)
#define STATUS_FAILURE             (0x00000001)
#define STATUS_INVALID_PARAMS      (0x00000002)
#define STATUS_UNSUPPORTED_FEATURE (0x00000003)

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
typedef int32_t status_t;

#ifdef __cplusplus
}
#endif

#endif /* STATUS_H */
