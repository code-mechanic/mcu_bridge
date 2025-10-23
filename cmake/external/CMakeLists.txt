if(${MCU_BRIDGE_HW} STREQUAL "stm32")
    add_subdirectory(
        ${MCU_BRIDGE_HW}
        ${CMAKE_BINARY_DIR}/external/stm32/${MCU_BRIDGE_MCU}_hal
    )
endif()
