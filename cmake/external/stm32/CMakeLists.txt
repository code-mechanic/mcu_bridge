################################################################################
# STM32 HAL Driver Build
#
# Usage:
#   - Set MCU_BRIDGE_MCU to select the STM32 family (e.g. stm32g0xx, stm32g4xx)
#   - Set MCU_BRIDGE_MCU_VERSION to select the specific MCU (e.g. stm32g474xx)
#
# Notes:
#   - All *_template.c files are excluded from build.
#   - For STM32G0 MCUs, old-style-declaration warnings are not treated as errors
################################################################################

# Print configuration summary
message(STATUS "Configuring STM32 HAL Driver for ${MCU_BRIDGE_MCU_VERSION} in ${MCU_BRIDGE_HW}")

# Target name
set(TARGET stm32_hal_driver)

# Paths
set(STM32_REPO_PATH ${MCU_BRIDGE_PATH}/external/stm32)
set(STM32_HAL_DRIVER_INC_PATH ${STM32_REPO_PATH}/${MCU_BRIDGE_MCU}_hal_driver/Inc)
set(STM32_HAL_DRIVER_SRC_PATH ${STM32_REPO_PATH}/${MCU_BRIDGE_MCU}_hal_driver/Src)
set(CMSIS_5_PATH ${MCU_BRIDGE_PATH}/external/CMSIS_5)

# Extract the MCU ID from the MCU version, e.g., "STM32G474xx" -> "g4"
string(SUBSTRING "${MCU_BRIDGE_MCU}" 5 2 STM32_MCU_ID)
string(TOLOWER "${STM32_MCU_ID}" STM32_MCU_ID_LOWER)
set(CMSIS_DEVICE_PATH ${STM32_REPO_PATH}/cmsis_device_${STM32_MCU_ID_LOWER})
message(STATUS "# Using CMSIS Device Path: ${CMSIS_DEVICE_PATH}")
message(STATUS "# Using HAL Path: ${STM32_HAL_DRIVER_SRC_PATH}")

# Gather source files, exclude templates
file(GLOB STM32_HAL_DRIVER_SRC_FILES "${STM32_HAL_DRIVER_SRC_PATH}/*.c")
list(FILTER STM32_HAL_DRIVER_SRC_FILES EXCLUDE REGEX ".*_template\\.c$")

# message(STATUS "STM HAL Driver Source Files to be built:")
# foreach(file ${STM32_HAL_DRIVER_SRC_FILES})
#     message(STATUS "  ${file}")
# endforeach()

# Build the HAL driver library
add_library(${TARGET} ${STM32_HAL_DRIVER_SRC_FILES})

# Special compile options for STM32G0 MCUs
if(MCU_BRIDGE_MCU_VERSION STREQUAL "stm32g0b0xx" OR 
   MCU_BRIDGE_MCU_VERSION STREQUAL "stm32g0b1xx" OR
   MCU_BRIDGE_MCU_VERSION STREQUAL "stm32g0c1xx")
    target_compile_options(${TARGET} PRIVATE -Wno-error=old-style-declaration)
endif()

# Include directories
target_include_directories(
  ${TARGET}
  PUBLIC ${STM32_HAL_DRIVER_INC_PATH}
  PUBLIC ${CMSIS_5_PATH}/CMSIS/Core/Include
  PUBLIC ${CMSIS_DEVICE_PATH}/Include
  PUBLIC ${MCU_BRIDGE_PATH}/config/${MCU_BRIDGE_HW})

# Define macro for selected MCU e.g., STM32G474xx
string(TOUPPER "${MCU_BRIDGE_MCU_VERSION}" MCU_FINAL_UP)
string(REPLACE "X" "x" MCU_FINAL "${MCU_FINAL_UP}")

message(STATUS "# Defined [MCU_HAL_MACRO] as ${MCU_FINAL}")
target_compile_definitions(${TARGET} PUBLIC "${MCU_FINAL}")
target_compile_definitions(${TARGET} PUBLIC "${MCU_FINAL}")
