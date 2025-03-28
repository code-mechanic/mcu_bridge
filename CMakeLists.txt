cmake_minimum_required(VERSION 3.15)

project(mcu_bridge)

# ~~~
# CMAKE_EXPORT_COMPILE_COMMANDS (CMAKE variable):
#   Enable/Disable output of compile commands during generation. If enabled,
#   generates a compile_commands.json file containing the exact compiler calls.
# ~~~
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# includes functions, variables common across all MCU_BRIDGE_HW
include(cmake/mcu_bridge.cmake)

# includes functions, variables specific to a given MCU_BRIDGE_HW
# MCU_BRIDGE_HW is passed from top level makefile
if((${MCU_BRIDGE_HW} STREQUAL hw_avr)
OR (${MCU_BRIDGE_HW} STREQUAL hw_pic)
OR (${MCU_BRIDGE_HW} STREQUAL hw_stm)
)
    include(product/${MCU_BRIDGE_HW}/cmake/${MCU_BRIDGE_HW}.cmake)
else()
    message( STATUS "MCU_BRIDGE_HW not set, so no product will be built" )
endif()

# display common variable values
mcu_bridge_show_config()

add_subdirectory(product)
add_subdirectory(source)
if(EXISTS test/)
if(${MCU_BRIDGE_TEST})
  add_subdirectory(test)
endif()
endif()
