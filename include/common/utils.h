/**
 * \addtogroup COMMON
 * @{
 */

/**
 * \file  utils.h
 * \brief Utility API
 */

#ifndef COMMON_H
#define COMMON_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <common/status.h>

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                          Definitions and Macros                          |
// |                                                                          |
// +--------------------------------------------------------------------------+

/** \brief Initialize a struct with zero value */
#define MB_ZERO_STRUCT(the_struct)                            \
    do {                                                      \
        uint32_t struct_size      = sizeof(the_struct);       \
        uint8_t* p_struct_element = (uint8_t*) (&the_struct); \
                                                              \
        while(struct_size-- > 0) { *p_struct_element++ = 0; } \
    } while(0)

/** \brief Return number of elements in array */
#define MB_ARRAY_LENGTH(p_array_ptr) (sizeof(p_array_ptr) / sizeof(*p_array_ptr))

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                          Definitions and Macros                          |
// |                                                                          |
// |                             Bit Manipulation                             |
// |                                                                          |
// +--------------------------------------------------------------------------+

/** \brief Sets the specific bit position(s) */
#define MB_BIT_SET(target, bitmask) ((target) |= ((unsigned) (bitmask)))

/** \brief Clears the specific bit position(s) */
#define MB_BIT_CLEAR(target, bitmask) ((target) &= ~((unsigned) (bitmask)))

/** \brief Toggles the specific bit position(s) */
#define MB_BIT_TOGGLE(target, bitmask) ((target) ^= ((unsigned) (bitmask)))

/**
 * \brief Validates the specific bit position(s)
 * returns true if the bit(s) set and false if the bit(s) clear.
 */
#define MB_BIT_TEST(target, bitmask) (((target) & ((unsigned) (bitmask))) == ((unsigned) (bitmask)))

/** \brief Masks the specific bit position */
#define MB_BIT_MASK(bit_num) (1 << (bit_num))

/** \cond EXCLUDE_DOCS */
/**
 * Bit Position defines
 */
#define MB_BIT0  (MB_BIT_MASK(0))
#define MB_BIT1  (MB_BIT_MASK(1))
#define MB_BIT2  (MB_BIT_MASK(2))
#define MB_BIT3  (MB_BIT_MASK(3))
#define MB_BIT4  (MB_BIT_MASK(4))
#define MB_BIT5  (MB_BIT_MASK(5))
#define MB_BIT6  (MB_BIT_MASK(6))
#define MB_BIT7  (MB_BIT_MASK(7))
#define MB_BIT8  (MB_BIT_MASK(8))
#define MB_BIT9  (MB_BIT_MASK(9))
#define MB_BIT10 (MB_BIT_MASK(10))
#define MB_BIT11 (MB_BIT_MASK(11))
#define MB_BIT12 (MB_BIT_MASK(12))
#define MB_BIT13 (MB_BIT_MASK(13))
#define MB_BIT14 (MB_BIT_MASK(14))
#define MB_BIT15 (MB_BIT_MASK(15))
#define MB_BIT16 (MB_BIT_MASK(16))
#define MB_BIT17 (MB_BIT_MASK(17))
#define MB_BIT18 (MB_BIT_MASK(18))
#define MB_BIT19 (MB_BIT_MASK(19))
#define MB_BIT20 (MB_BIT_MASK(20))
#define MB_BIT21 (MB_BIT_MASK(21))
#define MB_BIT22 (MB_BIT_MASK(22))
#define MB_BIT23 (MB_BIT_MASK(23))
#define MB_BIT24 (MB_BIT_MASK(24))
#define MB_BIT25 (MB_BIT_MASK(25))
#define MB_BIT26 (MB_BIT_MASK(26))
#define MB_BIT27 (MB_BIT_MASK(27))
#define MB_BIT28 (MB_BIT_MASK(28))
#define MB_BIT29 (MB_BIT_MASK(29))
#define MB_BIT30 (MB_BIT_MASK(30))
#define MB_BIT31 (MB_BIT_MASK(31))
/** \endcond */

/**
 * \brief Calculate total size of uint8_t bit array
 *
 * Example:
 * \code
 * uint8_t  my_bit_array[MB_BIT_UINT8_ARRAY_CALC_TOTAL_SIZE(10)];
 * \endcode
 */
#define MB_BIT_UINT8_ARRAY_CALC_TOTAL_SIZE(num_bits) (((num_bits) + 7U) / 8U)

/**
 * \brief Set specific bit in uint8_t bit array
 *
 * Example:
 * \code
 * uint8_t  my_bit_array[MB_BIT_UINT8_ARRAY_CALC_TOTAL_SIZE(10)];
 * MB_BIT_UINT8_ARRAY_SET_BIT(my_bit_array, 10);
 * \endcode
 */
#define MB_BIT_UINT8_ARRAY_SET_BIT(arr, index) ((arr)[(index) / 8U] |= (1U << ((index) % 8)))

/**
 * \brief Clear specific bit in uint8_t bit array
 *
 * Example:
 * \code
 * uint8_t  my_bit_array[MB_BIT_UINT8_ARRAY_CALC_TOTAL_SIZE(10)];
 * MB_BIT_UINT8_ARRAY_CLEAR_BIT(my_bit_array, 10);
 * \endcode
 */
#define MB_BIT_UINT8_ARRAY_CLEAR_BIT(arr, index) ((arr)[(index) / 8U] &= ~(1U << ((index) % 8)))

/**
 * \brief Toggle specific bit in uint8_t bit array
 *
 * Example:
 * \code
 * uint8_t  my_bit_array[MB_BIT_UINT8_ARRAY_CALC_TOTAL_SIZE(10)];
 * MB_BIT_UINT8_ARRAY_TOGGLE_BIT(my_bit_array, 10);
 * \endcode
 */
#define MB_BIT_UINT8_ARRAY_TOGGLE_BIT(arr, index) ((arr)[(index) / 8U] ^= (1U << ((index) % 8)))

/**
 * \brief Read specific bit in uint8_t bit array
 *
 * Example:
 * \code
 * uint8_t  my_bit_array[MB_BIT_UINT8_ARRAY_CALC_TOTAL_SIZE(10)];
 * MB_BIT_UINT8_ARRAY_READ_BIT(my_bit_array, 10);
 * \endcode
 */
#define MB_BIT_UINT8_ARRAY_READ_BIT(arr, index) (((arr)[(index) / 8U] >> ((index) % 8U)) & 1U)

/**
 * \brief Calculate total size of uint16_t bit array
 * Example:
 * \code
 * uint16_t  my_bit_array[MB_BIT_UINT16_ARRAY_CALC_TOTAL_SIZE(10)];
 * \endcode
 */
#define MB_BIT_UINT16_ARRAY_CALC_TOTAL_SIZE(num_bits) (((num_bits) + 15U) / 16U)

/**
 * \brief Set specific bit in uint8_t bit array
 *
 * Example:
 * \code
 * uint16_t  my_bit_array[MB_BIT_UINT16_ARRAY_CALC_TOTAL_SIZE(10)];
 * MB_BIT_UINT16_ARRAY_SET_BIT(my_bit_array, 10);
 * \endcode
 */
#define MB_BIT_UINT16_ARRAY_SET_BIT(arr, index) ((arr)[(index) / 16U] |= (1U << ((index) % 16)))

/**
 * \brief Clear specific bit in uint8_t bit array
 *
 * Example:
 * \code
 * uint16_t  my_bit_array[MB_BIT_UINT16_ARRAY_CALC_TOTAL_SIZE(10)];
 * MB_BIT_UINT16_ARRAY_CLEAR_BIT(my_bit_array, 10);
 * \endcode
 */
#define MB_BIT_UINT16_ARRAY_CLEAR_BIT(arr, index) ((arr)[(index) / 16U] &= ~(1U << ((index) % 16)))

/**
 * \brief Toggle specific bit in uint16_t bit array
 *
 * Example:
 * \code
 * uint16_t  my_bit_array[MB_BIT_UINT16_ARRAY_CALC_TOTAL_SIZE(10)];
 * MB_BIT_UINT16_ARRAY_TOGGLE_BIT(my_bit_array, 10);
 * \endcode
 */
#define MB_BIT_UINT16_ARRAY_TOGGLE_BIT(arr, index) ((arr)[(index) / 16U] ^= (1U << ((index) % 16)))

/**
 * \brief Read specific bit in uint16_t bit array
 *
 * Example:
 * \code
 * uint16_t  my_bit_array[MB_BIT_UINT16_ARRAY_CALC_TOTAL_SIZE(10)];
 * MB_BIT_UINT16_ARRAY_READ_BIT(my_bit_array, 10);
 * \endcode
 */
#define MB_BIT_UINT16_ARRAY_READ_BIT(arr, index) (((arr)[(index) / 16U] >> ((index) % 8U)) & 16U)

/**
 * \brief Calculate total size of uint32_t bit array
 *
 * Example:
 * \code
 * uint32_t  my_bit_array[MB_BIT_UINT32_ARRAY_CALC_TOTAL_SIZE(10)];
 * \endcode
 */
#define MB_BIT_UINT32_ARRAY_CALC_TOTAL_SIZE(num_bits) (((num_bits) + 31U) / 32U)

/**
 * \brief Set specific bit in uint32_t bit array
 *
 * Example:
 * \code
 * uint32_t  my_bit_array[MB_BIT_UINT32_ARRAY_CALC_TOTAL_SIZE(10)];
 * MB_BIT_UINT32_ARRAY_SET_BIT(my_bit_array, 10);
 * \endcode
 */
#define MB_BIT_UINT32_ARRAY_SET_BIT(arr, index) ((arr)[(index) / 16U] |= (1U << ((index) % 16)))

/**
 * \brief Clear specific bit in uint32_t bit array
 *
 * Example:
 * \code
 * uint32_t  my_bit_array[MB_BIT_UINT32_ARRAY_CALC_TOTAL_SIZE(10)];
 * MB_BIT_UINT32_ARRAY_CLEAR_BIT(my_bit_array, 10);
 * \endcode
 */
#define MB_BIT_UINT32_ARRAY_CLEAR_BIT(arr, index) ((arr)[(index) / 16U] &= ~(1U << ((index) % 16)))

/**
 * \brief Toggle specific bit in uint32_t bit array
 *
 * Example:
 * \code
 * uint32_t  my_bit_array[MB_BIT_UINT32_ARRAY_CALC_TOTAL_SIZE(10)];
 * MB_BIT_UINT32_ARRAY_TOGGLE_BIT(my_bit_array, 10);
 * \endcode
 */
#define MB_BIT_UINT32_ARRAY_TOGGLE_BIT(arr, index) ((arr)[(index) / 16U] ^= (1U << ((index) % 16)))

/**
 * \brief Read specific bit in uint32_t bit array
 *
 * Example:
 * \code
 * uint32_t  my_bit_array[MB_BIT_UINT32_ARRAY_CALC_TOTAL_SIZE(10)];
 * MB_BIT_UINT32_ARRAY_READ_BIT(my_bit_array, 10);
 * \endcode
 */
#define MB_BIT_UINT32_ARRAY_READ_BIT(arr, index) (((arr)[(index) / 16U] >> ((index) % 8U)) & 16U)

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                          Definitions and Macros                          |
// |                                                                          |
// |                                   Math                                   |
// |                                                                          |
// +--------------------------------------------------------------------------+

/** \brief Time conversion, microseconds to seconds */
#define MB_MATH_TIME_CONVERT_US_TO_SEC(_usf) ((float) (_usf) / 1000000.0f)

/** \brief Time conversion, nanoseconds to seconds */
#define MB_MATH_TIME_CONVERT_NS_TO_SEC(_nsf) ((float) (_nsf) / 1000000000.0f)

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                                 Typedefs                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                                Functions                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

/**
 * \brief   Convert float to string for printing
 *
 * This function is needed since some embedded sprintf do not support float printing
 *
 * \param[out]  str         Output string buffer
 * \param[in]   str_len     String buffer length in bytes
 * \param[in]   val         Float value to convert to string
 */
void float_to_str(char* str, size_t str_len, float val);

/**
 * \brief Convert hex character to an integer value
 *
 * \param[in]   hex_digit   Hex digit in [0-9a-fA-F]
 * \param[out]  p_val       Pointer to store integer value
 *
 * \return \ref status_t
 */
status_t hex_to_int(char hex_digit, uint8_t* p_val);

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                          Static inline Function                          |
// |                               Definition                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

#ifdef __cplusplus
}
#endif

#endif /* COMMON_H */

/** @} */

/**
 * \defgroup COMMON Common API
 */
