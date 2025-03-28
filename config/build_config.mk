#
# This makefile setups some makefile variables used across the MCU BRIDGE
#

MCU_BRIDGE_BUILD_ROOT=build
CMAKE_BUILD_PATH=$(MCU_BRIDGE_BUILD_ROOT)/$(MCU_BRIDGE_HW)

# List of supported product by SDK
MCU_BRIDGE_HW_SUPPORT_LIST += hw_pic
MCU_BRIDGE_HW_SUPPORT_LIST += hw_avr
MCU_BRIDGE_HW_SUPPORT_LIST += hw_stm

include product/$(MCU_BRIDGE_HW)/cmake/$(MCU_BRIDGE_HW)_build_config.mk

ifeq ($(shell uname), Linux)
  DOT := $(shell $(DOCKER) which dot)
else
  DOT := $(shell where dot 2>NUL)
endif

# ##########################
# # Compiler configuration #
# ##########################
# TOOLCHAIN = xc8
# CC = $(TOOLCHAIN)-cc
# CFLAGS = -mcpu=$(MCU_BRIDGE_MCU) -Wall -O0 -std=c99 -save-temps --memorysummary
