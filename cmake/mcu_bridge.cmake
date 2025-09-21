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
  message(STATUS "# Edit ./config/developement_config.mk to change below variable")
  mcu_bridge_show_variable(MCU_BRIDGE_HW)
  message(STATUS
    "# Edit ./product/${MCU_BRIDGE_HW}/cmake/${MCU_BRIDGE_HW}.cmake to change below variables"
  )
  if(MCU_BRIDGE_HW_VERSION)
    mcu_bridge_show_variable(MCU_BRIDGE_HW_VERSION)
  endif()
  mcu_bridge_show_variable(MCU_BRIDGE_MCU)
  mcu_bridge_show_variable(MCU_BRIDGE_MCU_VERSION)
  mcu_bridge_show_variable(MCU_BRIDGE_RTOS)
  if(MCU_BRIDGE_STM32G4_USBPD_LIB_TYPE)
    mcu_bridge_show_variable(MCU_BRIDGE_STM32G4_USBPD_LIB_TYPE)
  endif()
  message(STATUS "")

  message(STATUS "")
  message(STATUS "TOOLCHAIN configuration values,")
  message(STATUS
    "# Edit ./product/${MCU_BRIDGE_HW}/cmake/${MCU_BRIDGE_HW}_build_config.mk to change below variables"
  )
  mcu_bridge_show_variable(CMAKE_TOOLCHAIN_FILE)
  mcu_bridge_show_variable(TOOLCHAIN_PATH)
  message(STATUS "")

  message(STATUS "")
  message(STATUS "CMAKE configuration values,")
  message(STATUS "# Edit ./config/development_config.mk to change below variables")
  mcu_bridge_show_variable(CMAKE_BUILD_TYPE)
  mcu_bridge_show_variable(CMAKE_VERBOSE_MAKEFILE)
  message(STATUS "")

  message(STATUS "")
  message(STATUS "MCU BRIDGE feature enable ON/OFF flags,")
  message(STATUS
    "# Edit ./product/${MCU_BRIDGE_HW}/cmake/${MCU_BRIDGE_HW}.cmake to change below variables"
  )
  mcu_bridge_show_feature_flag(MCU_BRIDGE_COMMON_ALGORITHM)
  mcu_bridge_show_feature_flag(MCU_BRIDGE_COMMON_CLI)
  mcu_bridge_show_feature_flag(MCU_BRIDGE_COMMON_CONTROLLERS)
  mcu_bridge_show_feature_flag(MCU_BRIDGE_COMMON_CLI)
  mcu_bridge_show_feature_flag(MCU_BRIDGE_COMMON_CONTROLLERS)
  mcu_bridge_show_feature_flag(MCU_BRIDGE_COMMON_CURRENT_CONTROLLER)
  mcu_bridge_show_feature_flag(MCU_BRIDGE_COMMON_CURRENT_CONTROLLER_PCMC)
  mcu_bridge_show_feature_flag(MCU_BRIDGE_COMMON_GATEWAY)
  mcu_bridge_show_feature_flag(MCU_BRIDGE_COMMON_I2C_REG_SPACE)
  mcu_bridge_show_feature_flag(MCU_BRIDGE_COMMON_LOG)
  mcu_bridge_show_feature_flag(MCU_BRIDGE_COMMON_PROFILE)
  mcu_bridge_show_feature_flag(MCU_BRIDGE_COMMON_SW_WATCHDOG)
  mcu_bridge_show_feature_flag(MCU_BRIDGE_COMMON_USBPD_PIC_VDM)

  mcu_bridge_show_feature_flag(MCU_BRIDGE_HW_DEVICES_CHARGE_MCU_PLUTO)
  mcu_bridge_show_feature_flag(MCU_BRIDGE_HW_BMS_BQ76907_NTC_103AT)
  mcu_bridge_show_feature_flag(MCU_BRIDGE_HW_BMS_BQ76907_NTC_NTCLE203E3103SB0)

  message(STATUS "")

  if(EXISTS test/)
    message(STATUS "MCU BRIDGE test application enable ON/OFF flags,")
    mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST)
    if(${MCU_BRIDGE_TEST})
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_BLINKY)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_COMMON)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_CPU_BENCHMARKS)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_HELLO_WORLD)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_HW)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_LOG_AND_PROFILE)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_OSA)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_STM32G4_USBPD)
    endif()
    message(STATUS "")

    if(${MCU_BRIDGE_TEST_MCU})
      message(STATUS "MCU BRIDGE test_mcu individual tests enable ON/OFF flags,")
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_ADC)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_CMP)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_DMA)
      if(${MCU_BRIDGE_TEST_MCU_DMA})
        mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_DMA_TIM_TRIGERED_DMA)
        mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_DMA_M2M_LINK)
      endif()
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_GPIO)
      if(${MCU_BRIDGE_TEST_MCU_GPIO})
        mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_GPIO_LOOPBACK)
        if(${MCU_BRIDGE_TEST_MCU_GPIO_LOOPBACK})
          mcu_bridge_show_feature_flag(
            MCU_BRIDGE_TEST_MCU_GPIO_NUCLEO_STM32G474)
        endif()
        mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_GPIO_SET_PIN_DIR)
        mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_GPIO_SOFTWARE_INTR)
        mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_GPIO_BUTTON_INTR)
      endif()
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_I2C)
      if(${MCU_BRIDGE_TEST_MCU_I2C})
        mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_I2C_PHOBOS_LARGE)
      endif()
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_PWM)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_PWM_ADC_DMA)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_SPIM)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_UART)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_WATCHDOG)
      if(${MCU_BRIDGE_TEST_MCU_WATCHDOG})
        mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_WATCHDOG_PHOBOS_LARGE)
        mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_MCU_WATCHDOG_LAST)
      endif()
      message(STATUS "")
    endif()

    if(${MCU_BRIDGE_TEST_HW})
      message(STATUS "MCU BRIDGE test_hw individual tests enable ON/OFF flags,")
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_HW_EEPROM)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_HW_GPIO)
      message(STATUS "")
    endif()

    if(${MCU_BRIDGE_TEST_COMMON})
      message(STATUS "MCU BRIDGE test_common individual tests enable ON/OFF flags,")
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_COMMON_ALGORITHM)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_COMMON_CLI)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_COMMON_COMMON)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_COMMON_CONTROLLERS)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_COMMON_CURRENT_CONTROLLER)
      mcu_bridge_show_feature_flag(
        MCU_BRIDGE_TEST_COMMON_CURRENT_CONTROLLER_PCMC)
      mcu_bridge_show_feature_flag(
        MCU_BRIDGE_TEST_COMMON_CURRENT_CONTROLLER_POWER_STAGE)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_COMMON_I2C_REG_SPACE)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_COMMON_GATEWAY)
      mcu_bridge_show_feature_flag(MCU_BRIDGE_TEST_COMMON_SW_WATCHDOG)
      message(STATUS "")
    endif()
  endif()
endfunction()

function(mcu_bridge_show_variable VAR)
  message(STATUS "${VAR}=${${VAR}}")
endfunction()

function(mcu_bridge_show_feature_flag FEATURE_FLAG_VAR)
  if(${FEATURE_FLAG_VAR})
    message(STATUS "${FEATURE_FLAG_VAR}=ON")
  else()
    message(STATUS "${FEATURE_FLAG_VAR}=OFF")
  endif()
endfunction()
