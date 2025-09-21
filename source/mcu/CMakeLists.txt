foreach(MCU_BRIDGE_CONFIG ${MCU_BRIDGE_CONFIG_LIST})
  message(STATUS "--> Adding mcu bridge for ${MCU_BRIDGE_CONFIG}")
  add_subdirectory(
    ${MCU_BRIDGE_MCU}
    ${CMAKE_CURRENT_BINARY_DIR}/${MCU_BRIDGE_MCU}/${MCU_BRIDGE_CONFIG})
endforeach()
