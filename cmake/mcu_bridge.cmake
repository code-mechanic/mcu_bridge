# ~~~
# This file contains common functions and variables used by all cmake files.
# NOTE:
#  To avoid name conflicts with cmake built in functions and variables
# - functions are prefixed with mcu_bridge
# - variables are prefixed with MCU_BRIDGE
# ~~~

enable_language(CXX C ASM)

#~~~
# CMAKE_EXECUTABLE_SUFFIX (CMAKE variable):
#   The suffix for executables on the target platform.
#   The suffix to use for the end of an executable filename
#~~~
set(CMAKE_EXECUTABLE_SUFFIX ".elf")

#~~~
# MCU_BRIDGE_PATH (User defined variable):
# MCU_BRIDGE_HW (User defined variable):
# CMAKE_CURRENT_SOURCE_DIR (CMAKE variable):
#   This is the full path to the source directory that is currently being processed by cmake
# CMAKE_TOOLCHAIN_FILE (CMAKE variable):
#~~~
set(MCU_BRIDGE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
set(MCU_BRIDGE_HW
    "none"
    CACHE STRING "MCU BRIDGE HW Platform")
set(CMAKE_TOOLCHAIN_FILE
    "none"
    CACHE STRING "CMake Toolchain file")

# This function adds linker options and linker dependencies for a specified
# linker script file
#~~~
# target_link_options (CMake command):
#   Used to specify linker options for a particular target. These options are 
#   passed directly to the linker when building the target
# set_target_properties (CMAKE command):
#   Used to specify properties for a particular target.
#   Property: LINK_DEPENDS (CMake property):
#     list of full-paths to linker files on which the link rule for this target depends
#~~~
function(mcu_bridge_target_set_linker_script_and_memory_map_file TARGET
         LINKER_SCRIPT)
  target_link_options(
    ${TARGET} PUBLIC ${TOOLCHAIN_SET_LINKER_SCRIPT_PREFIX}${LINKER_SCRIPT}
    ${TOOLCHAIN_SET_MAP_PREFIX}${TARGET}.map)

  set_target_properties(${TARGET} PROPERTIES LINK_DEPENDS ${LINKER_SCRIPT})
endfunction()

# ~~~
# This function adds compiler defines to support logging for a given module
#
# TARGET is the cmake library to which these compiler defines will be added
#
# MODULE_NAME is the name to give to this module. Keep the module name within 8
#             characters
#
# MODULE_LOG_LEVEL is log severity level that should be enabled for
#                  this module. Valid values for log level are
#                  NONE, ERROR, WARN, INFO, DEBUG, ALL
#                  NONE will disable all logging for this module
#                  ALL will enable all logging levels for this module
#
# target_compile_definitions (CMake command):
#   used to define preprocessor macros (compile-time constants) for a specific target.
#   These macros can be used to control conditional compilation in source code
# ~~~
function(mcu_bridge_add_log_module TARGET MODULE_NAME MODULE_LOG_LEVEL)
  target_compile_definitions(${TARGET}
                             PRIVATE LOG_${MODULE_NAME}_STR="${MODULE_NAME}")
  target_compile_definitions(
    ${TARGET} PRIVATE LOG_${MODULE_NAME}_LEVEL=LOG_LEVEL_${MODULE_LOG_LEVEL})
endfunction(mcu_bridge_add_log_module)

# This function displays common variable values used by all cmake files
function(mcu_bridge_show_config)

  message(STATUS "")
  message(STATUS "MCU BRIDGE configuration values,")
  mcu_bridge_show_variable(MCU_BRIDGE_PATH)
  message(STATUS "")

  message(STATUS "# Edit ./config/developement_config.mk to change below variable")
  mcu_bridge_show_variable(MCU_BRIDGE_HW)
  mcu_bridge_show_variable(MCU_BRIDGE_MCU)
  mcu_bridge_show_variable(MCU_BRIDGE_MCU_VERSION)
  message(STATUS "")

  message(STATUS "TOOLCHAIN configuration values,")
  message(STATUS
    "# Edit ./config/${MCU_BRIDGE_HW}/${MCU_BRIDGE_HW}_build_config.mk to change below variables"
  )
  mcu_bridge_show_variable(CMAKE_TOOLCHAIN_FILE)
  mcu_bridge_show_variable(TOOLCHAIN_PATH)
  message(STATUS "")

  message(STATUS "CMAKE configuration values,")
  message(STATUS "# Edit ./config/development_config.mk to change below variables")
  mcu_bridge_show_variable(CMAKE_BUILD_TYPE)
  mcu_bridge_show_variable(CMAKE_VERBOSE_MAKEFILE)
  message(STATUS "")

  message(STATUS "MCU BRIDGE feature enable ON/OFF flags,")
  message(STATUS "# Edit ./config/${MCU_BRIDGE_HW}/${MCU_BRIDGE_HW}.cmake to change below variables")
  mcu_bridge_show_feature_flag(MCU_BRIDGE_COMMON_LOG)
  message(STATUS "")
endfunction()

function(mcu_bridge_show_variable VAR)
  message(STATUS "[${VAR}] = ${${VAR}}")
endfunction()

function(mcu_bridge_show_feature_flag FEATURE_FLAG_VAR)
  if(${FEATURE_FLAG_VAR})
    message(STATUS "${FEATURE_FLAG_VAR}=ON")
  else()
    message(STATUS "${FEATURE_FLAG_VAR}=OFF")
  endif()
endfunction()
