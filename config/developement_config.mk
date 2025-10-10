
#
# This defines make variables which a user will likely change based
# on their day to day development needs
#

# Valid values are any directory name under mcu_platform/
MCU_BRIDGE_HW?=stm32
MCU_BRIDGE_MCU?=stm32g4xx
MCU_BRIDGE_MCU_VERSION?=stm32g474xx

# Valid values: Debug, Release
CMAKE_BUILD_TYPE?=Release

# Valid values: ON, OFF
CMAKE_VERBOSE_MAKEFILE?=OFF
