#
# Refer https://github.com/enbyted/xc8-cmake-template/tree/xc8-cc for config details
#

# Pre configuration/PreLoad.cmake configuration of toolchain
set(MICROCHIP_XC8_MODE "free" CACHE INTERNAL "" FORCE)
set(MICROCHIP_MCU ${MCU_BRIDGE_MCU})
string(TOUPPER "${MICROCHIP_MCU}" MICROCHIP_MCU)

# Toolchain include
include(/home/mcu_bridge/cmake/toolchain/cmake_microchip/toolchain.cmake)

# Post configuration of toolchain
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_RELEASE "-O2")
