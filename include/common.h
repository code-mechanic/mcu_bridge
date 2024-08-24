#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stddef.h>

/* Exported types ------------------------------------------------------------*/
typedef enum bool_et_ {
  FALSE = 0,
  TRUE
} bool_et;

typedef enum status_et_{
  FAILED = 0,
  SUCCESS,
  BUSY,
  TIMEOUT
} status_et;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
#define DISABLE                                                             (0U)
#define ENABLE                                                              (1U)

/* Exported functions ------------------------------------------------------- */

#ifdef __cplusplus
}
#endif

#endif /* COMMON_H */

