set(TARGET ${MCU_BRIDGE_HW}_bridge_headers)

# create stm32_bridge_headers library
# create ti_bridge_headers library
# create avr_bridge_headers library
# create pic_bridge_headers library
add_library(${TARGET} INTERFACE)

target_include_directories(
    ${TARGET} 
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(
    ${TARGET}
    INTERFACE mcu_headers
)
