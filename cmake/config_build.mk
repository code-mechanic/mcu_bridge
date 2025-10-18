#
# This makefile setups some makefile variables used across the MCU BRIDGE
#

MCU_BRIDGE_BUILD_ROOT=build
CMAKE_BUILD_PATH=$(MCU_BRIDGE_BUILD_ROOT)/$(MCU_BRIDGE_HW)

include config/${MCU_BRIDGE_HW}/$(MCU_BRIDGE_HW)_build_config.mk

# List of supported product by SDK
MCU_BRIDGE_HW_SUPPORT_LIST += stm32
MCU_BRIDGE_HW_SUPPORT_LIST += pic

ifeq ($(shell uname), Linux)
  DOT := $(shell $(DOCKER) which dot)
else
  DOT := $(shell where dot 2>NUL)
endif
