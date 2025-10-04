/*
 * Includes should be first within the source file
 *
 *   Possibly with some #ifdef interaction if needed
 */
#include <stddef.h>
#include <stdbool.h>
#include <my_module.h>

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                          Definitions and Macros                          |
// |                                                                          |
// +--------------------------------------------------------------------------+

/*
 * This section should include all local #defines and Macros
 *
 *   Naming conventions same as public defines and macros
 */

/** \brief A brief description */
#define MY_MODULE_LOCAL_DEFINE (1u)

/*
 * Macros should have a "function like" header to describe usage/purpose
 */

/**
 * \brief A brief description
 *
 * \param[in]     x : parameter that is read only for this func
 * \param[out]    y : parameter who's value is set by this func
 * \param[in/out] z : parameter who's value may be used internally and modified
 * \return some result that is returned
 */
#define MY_MODULE_LOCAL_MACRO(x, y, z) ((x) + (y) + (z))

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                                 Typedefs                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

/*
 * This section should include all local structs and enums
 *
 *   Naming conventions same as public enums and structs
 */

/**
 * \brief Enum description of what it does
 */
typedef enum my_module_opcode_t_ {
    MY_MODULE_OPCODE_INVALID = 0,
    MY_MODULE_OPCODE_1,
    MY_MODULE_OPCODE_2,
    MY_MODULE_OPCODE_3,
    MY_MODULE_OPCODE_MAX
} my_module_opcode_t;

/**
 * \brief Struct description of what/why
 */
typedef struct my_module_local_struct_t_ {
    uint8_t  my_variable_1; /// < Var description
    uint32_t my_variable_2; ///< Var description
} my_module_local_struct_t;

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                           Function Prototypes                            |
// |                                                                          |
// +--------------------------------------------------------------------------+

/*
 * Forward declarations for private funcs
 *
 *   Private funcs should be static
 *   Naming conventions same as public functions
 *
 *   This helps quickly identify the functions as local to this source
 *   These can be forward defined only when required
 *
 *   Private funcs are defined before Private variables in case of use
 *   in tables
 */

static void my_module_my_local_func(uint32_t param1, uint32_t param2);
static void my_module_do_this();
static void my_module_do_that();
static void my_module_on_timer_expired();
static void my_module_on_my_isr();

/*
 * Avoid extern'ing functions outside of this module/source
 *
 *   Instead, define them in the public module header file
 */
extern void my_module_avoid_extern_module_function(void);

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                          Variable Declarations                           |
// |                                                                          |
// +--------------------------------------------------------------------------+

/*
 * Variables global to this file but not accessible by external modules.
 *
 *   Naming conventions same as public symbols
 *
 *   Variables should be static
 *   Variables should begin with g_
 *
 * Here, these would typically be referred to as "global" variables,
 *   but any global variable that needs access from other modules
 *   should have access functions (get/set)
 *
 */
static uint32_t g_my_module_private_global_variable;

/*
 * Avoid externing globals variables
 *
 *   Instead create get/set functions (or macros)
 *   within the module that "owns" the global variable
 */
extern uint32_t g_my_module_avoid_extern_variable;

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                  Public                                  |
// |                                Functions                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

/*
 * Public functions are documented using doxygen tags in public header
 * and need not be documented again in the .c file
 */

uint32_t my_module_public_func(void)
{
    uint32_t           this_variable = 0;
    bool               this_is_valid = true;
    my_module_opcode_t opcode        = MY_MODULE_OPCODE_1;
    int32_t            ret_val       = 0;

    /*
     * POINTERS
     *
     * Use p prefix (or pp for pointer to pointer)
     * For global pointers, use gp_
     *
     * In general, Hungarian notation is frowned on,
     *   However, noting pointers improves readability
     */
    uint32_t* p_var = NULL;

    /*
     * IF/ELSE statements
     *
     * Always use brackets for if statements
     * Avoid same line if statements such as
     *   if (this_is_valid) do_that();
     */
    if(this_is_valid) {
        my_module_do_this();
    } else {
        my_module_do_that();
    }

    /*
     * CONSTANTS
     *
     * Avoid using constants in code
     *   in if/else statements
     *   in case statements
     *   in default value assignments
     *   for boolean, use true/false instead of 0/1
     *
     * Instead, define constants and comment as to what/why the value exists
     */
    if(this_variable > 10) // this is bad
    {
        my_module_do_this();
    }

    /*
     * SWITCH statements
     *
     * Avoid complex operations in cases,
     *   Instead, create subroutines (can be INLINE) to handle cases
     * For very simple cases, no brackets are better for readability
     * For multiline case handlers, brackets may improve readability
     */
    switch(opcode) {
        case MY_MODULE_OPCODE_1:
            my_module_do_this();
            break;

        case MY_MODULE_OPCODE_2:
            {
                if(this_is_valid) {
                    my_module_do_this();
                } else {
                    my_module_do_that();
                }
            }
            break;

        default:
            break;

    } // switch( opcode )

    /* below lines are just to make this file compile without warnings */
    (void) p_var;
    (void) g_my_module_private_global_variable;
    my_module_my_local_func(0, 0);
    my_module_on_my_isr();
    my_module_on_timer_expired();

    return ret_val;
}

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                                Functions                                 |
// |                                                                          |
// +--------------------------------------------------------------------------+

/*
 * All functions private to this source file
 *   Naming conventions same as public functions
 *   Funcs should be static
 *
 * Group common functionality within multiple private sections if desired
 */

/**
 * \brief Function description
 *
 * \param[in]  param1   parameter that is read only for this func
 * \param[out] p_param2 parameter who's value is set by this func
 *
 * \return describe the return value
 */
static void my_module_my_local_func(uint32_t param1, uint32_t* p_param2)
{
}

static void my_module_do_this()
{
}

static void my_module_do_that()
{
}

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                                 Private                                  |
// |                            Callback Handlers                             |
// |                                                                          |
// +--------------------------------------------------------------------------+

/*
 * This does not necessarily need to be a different "section"
 *
 * Placeholder for things like
 *   Timer callbacks
 *   ISR callbacks
 *   Generally, "system" callbacks
 *
 * These funcs typically have an on_<event> style naming
 *   Ex. on_timer
 *       on_irq, on_isr
 */

static void my_module_on_timer_expired(void)
{
}

/*
 * Avoid major computations and excess processing time within ISRs
 */
static void my_module_on_my_isr(void)
{
}

// +--------------------------------------------------------------------------+
// |                                                                          |
// |                           Test / Debug / CLI                             |
// |                                                                          |
// +--------------------------------------------------------------------------+

/*
 * Add all nonessential (non-release) code here
 *
 * However don't leave commented out code in the file
 */
