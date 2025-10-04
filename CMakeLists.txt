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

# includes functions, variables specific to the selected MCU_BRIDGE_HW
include(config/${MCU_BRIDGE_HW}/${MCU_BRIDGE_HW}.cmake)

# display common variable values
mcu_bridge_show_config()

# MCU bridge header interfaces
add_library(mcu_bridge_headers INTERFACE)
target_include_directories(mcu_bridge_headers
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include/common)

add_subdirectory(cmake)
add_subdirectory(source)
add_subdirectory(mcu_platform)
