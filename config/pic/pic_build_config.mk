#
# This file defines paths to tools needed to build
#

# No need to export below, these are pass as arguments to cmake by top level makefile
CMAKE_TOOLCHAIN_FILE=cmake/toolchain/pic_toolchain-xc8-cc.cmake
TOOLCHAIN_PATH=/opt/microchip/xc8/v2.50

# This variable is used to pass HW specific cmake arguments to top level cmake command
MCU_BRIDGE_HW_ADDITIONAL_CMAKE_OPTIONS=