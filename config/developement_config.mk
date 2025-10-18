
#
# This defines make variables which a user will likely change based
# on their day to day development needs
#

# Valid values are,
# 
# stm32
# pic
MCU_BRIDGE_HW?=stm32

# Valid values are,
# 
# For stm32: stm32f0xx, stm32f1xx, stm32g0xx, stm32g4xx etc
# For pic: use `make pic_xc8_list_mcu` to get the list of valid values
MCU_BRIDGE_MCU?=stm32g4xx

# Valid values are,
# 
# For stm32: stm32g474xx etc
# For pic: use `make pic_xc8_list_mcu` to get the list of valid values
MCU_BRIDGE_MCU_VERSION=stm32g474xx

ifeq (${MCU_BRIDGE_HW}, pic)
	MCU_BRIDGE_MCU_VERSION=${MCU_BRIDGE_MCU}
endif

# Valid values: Debug, Release
CMAKE_BUILD_TYPE?=Release

# Valid values: ON, OFF
CMAKE_VERBOSE_MAKEFILE?=OFF

# Valid values: all, gpio
MCU_BRIDGE_EXAMPLE?=all
