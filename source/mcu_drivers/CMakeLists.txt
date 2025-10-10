set(TARGET mcu_bridge_drivers)

# MCU bridge Driver
add_library(
    ${TARGET}
    mcu_gpio.c
)

target_link_libraries(
    ${TARGET}
    PUBLIC mcu_bridge_headers
)
