set(TARGET ${MCU_BRIDGE_HW}_bridge_drivers)

# create pic_bridge_drivers library
add_library(
    ${TARGET}
    pic_init.c
    pic_gpio.c
    pic_check_macro.c
)

target_compile_definitions(
    ${TARGET}
    PUBLIC PIC_CONFIG_BITS_HEADER="configuration_bits.h"
)

target_link_libraries(
    ${TARGET}
    PUBLIC mcu_bridge_cfg      # To access macro from config/mcu_bridge_cfg.h
    PUBLIC ${MCU_BRIDGE_HW}_bridge_headers  # To access source/mcu_bridge folder
)
