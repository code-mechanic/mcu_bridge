#
# This function converts a cmake target executable file, e.g elf file into a
# format that can be flashed and booted by the MCU bootloader
#
# This function needs to be defined by every MCU_BRIDGE_HW cmake file since the
# exact command used to make a flashable binary is specific to that
# MCU_BRIDGE_HW
#
function(mcu_bridge_make_flash_image EXECUTABLE)
  add_custom_command(
    TARGET ${EXECUTABLE}
    POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} ARGS -O binary ${EXECUTABLE}.elf ${EXECUTABLE}.bin)
endfunction()
