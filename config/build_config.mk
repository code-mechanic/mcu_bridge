#
# This makefile setups some makefile variables used across the PIC SDK
#

######################
# User configuration #
######################
PIC_SDK_MCU ?= pic16f877a

#####################
# SDK configuration #
#####################
EXECUTABLE := $(PIC_SDK_MCU)
BUILD_PATH := build/$(PIC_SDK_MCU)

# Initialize the SRC_PATH variable
SRC_PATH += source/common_drivers
SRC_PATH += source/$(PIC_SDK_MCU)
SRC_PATH += test/$(PIC_SDK_MCU)

# Initialize the INC_PATH variable
INC_PATH += include
INC_PATH += include/mcu/config
INC_PATH += include/mcu/drivers
INC_PATH += source/common_drivers/dispatch

# List of supported MCU by SDK
PIC_SDK_MCU_SUPPORT_LIST += pic16f877a

##########################
# Compiler configuration #
##########################
TOOLCHAIN = xc8
CC = $(TOOLCHAIN)-cc
CFLAGS = -mcpu=$(PIC_SDK_MCU) -Wall -O0 -std=c99 -save-temps --memorysummary
