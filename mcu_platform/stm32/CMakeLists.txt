# STM32 interfaces
add_library(stm32_bridge_headers INTERFACE)
target_include_directories(stm32_bridge_headers
  INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

set(TARGET stm32_bridge_driver)

add_library(
  ${TARGET}
  source/stm32_gpio.c)

target_link_libraries(${TARGET}
  PRIVATE mcu_bridge_headers
  PRIVATE stm32_bridge_headers
  PRIVATE stm32_hal_driver)

configure_file(
    ${MCU_BRIDGE_PATH}/config/${MCU_BRIDGE_HW}/${MCU_BRIDGE_HW}_config.h.in
    ${CMAKE_BINARY_DIR}/generated/${MCU_BRIDGE_HW}_config.h
)

target_include_directories(${TARGET} PUBLIC ${CMAKE_BINARY_DIR}/generated)
