#
# This file defines paths to tools needed to build
#

# No need to export below, these are pass as arguments to cmake by top level makefile
CMAKE_TOOLCHAIN_FILE=cmake/toolchain/stm32g4_toolchain-arm-none-eabi.cmake
TOOLCHAIN_PATH=/opt/gcc-arm-none-eabi-10.3-2021.10

# This variable is used to pass HW specific cmake arguments to top level cmake command
MCU_BRIDGE_HW_ADDITIONAL_CMAKE_OPTIONS=