set(TARGET mcu_bridge_driver)

add_library(
  ${TARGET}
  mcu_gpio.c)

target_link_libraries(${TARGET} PRIVATE mcu_bridge_headers)
