set(TARGET mcu_bridge_drivers)

# MCU bridge Driver
add_library(
    ${TARGET}
    mcu_gpio.c
)

target_link_libraries(
    ${TARGET}
    PUBLIC ${MCU_BRIDGE_HW}_bridge_drivers # Link implemenation of mcu_bridge/mcu_*_bridge.h
)
