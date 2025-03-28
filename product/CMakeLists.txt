# allow developers to specify their own products
# "none" is the default value set in cmake/mcu_bridge.cmake
if (NOT ${MCU_BRIDGE_HW} STREQUAL "none")
  add_subdirectory(${MCU_BRIDGE_HW})
endif()
