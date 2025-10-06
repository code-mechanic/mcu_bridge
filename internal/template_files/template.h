/**
 * \defgroup MY_MODULE My module API
 * \ingroup MY_MODULE_PARENT
 *
 * This file is a template to show how to write
 * .h and .c files using the defined coding guidelines and naming
 * conventions. See also \ref coding_guidelines
 *
 * @{
 */

/**
 * \file my_module.h
 * \brief My module API
 */
#ifndef MY_MODULE_H
#define MY_MODULE_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                          Definitions and Macros                          |
// |                                                                          |
// +--------------------------------------------------------------------------+

/**
 * \brief Public defines should use module's name as prefix
 */
#define MY_MODULE_DEFINITION (1u)

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                                 Typedefs                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

/**
 * \brief Enum description of what it does
 *
 *  Public enums/structs should use module's name as prefix
 *
 *   - Enum names should be snake case
 *   - Enum names should end with _t
 *   - Enum members should be capital case
 *   - Enum members should include enum name
 */
typedef enum my_module_list_t_ {
    /**
     * \brief First enum should represent a INVALID value
     *
     * This is an example of multi-line description of enum.
     * Same can be used for struct fields
     */
    MY_MODULE_LIST_INVALID = 0,
    MY_MODULE_LIST_1, /**< This is example of a single-line description */
    MY_MODULE_LIST_2,
    MY_MODULE_LIST_3,
    /**
     * \brief This should be the last value
     *
     * INVALID and MAX values help to do parameter validation
     */
    MY_MODULE_LIST_MAX

} my_module_list_t;

/**
 * \brief Struct description of what it does
 *
 * - Struct names should be snake case.
 * - Struct names should end with _t.
 * - Struct field should be snake case
 *
 */
typedef struct my_module_struct_t_ {

    uint8_t index; /**< Var description */

} my_module_struct_t;

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                                Functions                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

/**
 * \name Initialization functions
 *
 *  @{
 */

 /**
 * \brief Function description
 *
 * \param[in]  param1   parameter that is read only for this func
 * \param[out] p_param2 parameter who's value is set by this func
 *
 * \return describe the return value
 */
int32_t my_module_init(uint32_t param1, uint32_t* p_param2);

/** @} */

/**
 * \name Setup functions
 *
 *  @{
 */

void my_module_setup(uint32_t param1, uint32_t* p_param2);

/** @} */

/**
 * \name Run-time functions
 *
 *  @{
 */

void my_module_run(uint32_t param1, uint32_t* p_param2);

/** @} */

#ifdef __cplusplus
}
#endif

#endif // MY_MODULE_H

/** @} */

/**
 * \defgroup MY_MODULE_PARENT Template file
 */
