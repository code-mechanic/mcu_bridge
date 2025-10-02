set(TARGET stm32_hal_driver)

set(STM32_REPO_PATH ${MCU_BRIDGE_PATH}/external/stm32)
set(STM32_HAL_DRIVER_INC_PATH ${STM32_REPO_PATH}/${MCU_BRIDGE_MCU}-hal-driver/Inc)
set(STM32_HAL_DRIVER_SRC_PATH ${STM32_REPO_PATH}/${MCU_BRIDGE_MCU}-hal-driver/Src)
set(CMSIS_5_PATH ${MCU_BRIDGE_PATH}/external/CMSIS_5)

# Extract the MCU ID from the MCU version, e.g., "STM32G474xx" -> "g4"
# string(SUBSTRING <string> <begin> <length> <output_variable>)
string(SUBSTRING "${MCU_BRIDGE_MCU_VERSION}" 5 2 STM32_MCU_ID)
string(TOLOWER "${STM32_MCU_ID}" STM32_MCU_ID_LOWER)
set(CMSIS_DEVICE_PATH ${STM32_REPO_PATH}/cmsis-device-${STM32_MCU_ID_LOWER})


file(GLOB STM32_HAL_DRIVER_SRC_FILES "${STM32_HAL_DRIVER_SRC_PATH}/*.c")

# message(STATUS "STM HAL Driver Source Files to be built:")
# foreach(file ${STM32_HAL_DRIVER_SRC_FILES})
#     message(STATUS "  ${file}")
# endforeach()

add_library(${TARGET} ${STM32_HAL_DRIVER_SRC_FILES})

target_include_directories(
  ${TARGET}
  PUBLIC ${STM32_HAL_DRIVER_INC_PATH}
  PUBLIC ${CMSIS_5_PATH}/CMSIS/Core/Include
  PUBLIC ${CMSIS_DEVICE_PATH}/Include
  PUBLIC ${MCU_BRIDGE_PATH}/config/${MCU_BRIDGE_HW})

# Create the define for the specific MCU, e.g., STM32G474xx
# Remove last two characters ("xx")
string(LENGTH "${MCU_BRIDGE_MCU_VERSION}" STM32_MCU_LEN)
math(EXPR KEEP_LEN "${STM32_MCU_LEN} - 2")
string(SUBSTRING "${MCU_BRIDGE_MCU_VERSION}" 0 ${KEEP_LEN} STM32_MCU_PREFIX)
# Uppercase everything except the last two
string(TOUPPER "${STM32_MCU_PREFIX}" STM32_MCU_PREFIX_UP)
# Hardcode "xx" at the end
set(STM32_MCU_FINAL "${STM32_MCU_PREFIX_UP}xx")
message(STATUS "Defined [STM32_MCU_FINAL] as ${STM32_MCU_FINAL}")

target_compile_definitions(${TARGET} PUBLIC "USE_FULL_LL_DRIVER")
target_compile_definitions(${TARGET} PUBLIC "${STM32_MCU_FINAL}")
