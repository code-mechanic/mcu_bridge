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

# display common variable values
mcu_bridge_show_config()

# MCU bridge header interfaces
add_library(mcu_headers INTERFACE)
target_include_directories(mcu_headers
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# propagate selected MCU_BRIDGE_HW to subdirectories
string(TOUPPER "${MCU_BRIDGE_HW}" MCU_BRIDGE_HW_MACRO)
add_compile_definitions(${MCU_BRIDGE_HW_MACRO})

add_subdirectory(config)
add_subdirectory(cmake)
add_subdirectory(source)

if(EXISTS example/)
  add_subdirectory(example)
endif()
