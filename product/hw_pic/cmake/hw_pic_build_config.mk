#
# This file defines paths to tools needed to build this product
#

# No need to export below, these are pass as arguments to cmake by top level makefile
CMAKE_TOOLCHAIN_FILE=cmake/toolchain/pic16f_toolchain-xc8.cmake
TOOLCHAIN_PATH=/opt/xc8/v2.40/bin

# This variable is used to pass HW specific cmake arguments to top level cmake command
MCU_BRIDGE_HW_ADDITIONAL_CMAKE_OPTIONS=
