# -----------------------------------------------------------------##
# CMake arm-none-eabi toolchain file for STM32L1 series processors ##
# -----------------------------------------------------------------##

# Append current directory to CMAKE_MODULE_PATH for making device specific cmake
# modules visible
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# ------------------#
# Target definition #
# ------------------#

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR ARM)

# -----------------------------------#
# Set toolchain paths and extensions #
# -----------------------------------#

set(TOOLCHAIN arm-none-eabi)

# ~~~
# This toolchain cmake file will be used by CMake multiple times.
# Here, an argument passed would go out of scope.
# To prevent this, append the argument to CMAKE_TRY_COMPILE_PLATFORM_VARIABLES
# ~~~
list(APPEND CMAKE_TRY_COMPILE_PLATFORM_VARIABLES DOCKER_IMG)
list(APPEND CMAKE_TRY_COMPILE_PLATFORM_VARIABLES TOOLCHAIN_PATH)

# Check if TOOLCHAIN_PATH is valid for non-docker based build environment. For
# docker based build environment, this would fail if invoked with `docker exec`
# command outside of docker (since in this case EXISTS check is performed for
# local file system)
if("${DOCKER_IMG}" STREQUAL "")
  if(NOT EXISTS ${TOOLCHAIN_PATH})
    # If default TOOLCHAIN_PATH is invalid, check for GCC_ARM_NONE_EABI_PATH env
    # variable.
    file(TO_CMAKE_PATH "$ENV{GCC_ARM_NONE_EABI_PATH}" TOOLCHAIN_PATH)
    if(NOT EXISTS ${TOOLCHAIN_PATH})
      message(
        FATAL_ERROR
          "Toolchain path doesn't exist!! \nSet 'GCC_ARM_NONE_EABI_PATH' env variable!!"
      )
    endif()
  endif()
endif()

set(TOOLCHAIN_BIN_DIR ${TOOLCHAIN_PATH}/bin)
set(TOOLCHAIN_INC_DIR ${TOOLCHAIN_PATH}/${TOOLCHAIN}/include)
set(TOOLCHAIN_LIB_DIR ${TOOLCHAIN_PATH}/${TOOLCHAIN}/lib)

set(TOOLCHAIN_EXT "")
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL Windows)
  set(TOOLCHAIN_EXT ".exe")
endif()

# Perform compiler test with static library
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# --------------------------------#
# Set local Compiler/Linker Flags #
# --------------------------------#

# ~~~
# STM32L1 MCU specific flags
# -mcpu                 Build for Arm v7-m Cortex-M3
# -mthumb               Use the thumb instruction set
# ~~~
set(STM32L1_MCU_FLAGS "-mcpu=cortex-m3 -mthumb")

# ~~~
# Generic Object Flags
# -g                            Produce debugging information in the operating system’s native format.
# -Wall                         Print standard warnings
# -Wextra                       Print extra warnings
# -Werror                       Treat detected warnings as errors
# -fno-builtin                  Do not use built-in functions provided by GCC.
# -ffunction-sections           Place each function item into its own section in the output file.
# -fdata-sections               Place each data item into its own section in the output file.
# -fomit-frame-pointer          Omit the frame pointer in functions that don’t need one.
# -Wmissing-field-initializers  Throw warnings for struct initializations that don't hit every member
# ~~~
set(OBJECT_GEN_FLAGS
    "-g -Wall -Wextra -Werror -fno-builtin -ffunction-sections -fdata-sections -fomit-frame-pointer -Wmissing-field-initializers -Wno-unused-parameter"
)

# --------------------------------#
# Set CMake Compiler/Linker Flags #
# --------------------------------#

# ~~~
# C Flags
# -std=gnu99            Follow the C-99 Standard
# ~~~
set(CMAKE_C_FLAGS
    "${STM32L1_MCU_FLAGS} ${OBJECT_GEN_FLAGS} -std=gnu99 "
    CACHE INTERNAL "C Compiler options")

# ~~~
# C++ Flags
# -std=c++17            Follow the C++ 17 Standard
# ~~~
set(CMAKE_CXX_FLAGS
    "${STM32L1_MCU_FLAGS} ${OBJECT_GEN_FLAGS} -std=c++17 -fno-rtti -fno-exceptions -fno-threadsafe-statics -fno-unwind-tables -fmessage-length=0 -funsigned-char"
    CACHE INTERNAL "C++ Compiler options")

# ~~~
# ASM Flags
# -x assembler-with-cpp Allow C directives in assembly files
# ~~~
set(CMAKE_ASM_FLAGS
    "${STM32L1_MCU_FLAGS} ${OBJECT_GEN_FLAGS} -x assembler-with-cpp "
    CACHE INTERNAL "ASM Compiler options")

# ~~~
# Linker Flags
# --specs=nano.specs    Link with newlib-nano.
# --specs=nosys.specs   No syscalls, provide empty implementations for the POSIX system calls.
# -Wl,-Map              Generate a map file
# -Wl,--gc-sections     Perform the dead code elimination.
# ~~~
set(CMAKE_EXE_LINKER_FLAGS
    "${STM32L1_MCU_FLAGS} --specs=nano.specs --specs=nosys.specs -Wl,--gc-sections -Wl,--print-memory-usage"
    CACHE INTERNAL "Linker options")

# ----------------------------------------------#
# Set debug/release build configuration Options #
# ----------------------------------------------#

# ~~~
# Options for DEBUG build
# -Og   Enables optimizations that do not interfere with debugging.
# ~~~
set(CMAKE_C_FLAGS_DEBUG
    "-D_DEBUG -Og"
    CACHE INTERNAL "C Compiler options for debug build type")
set(CMAKE_CXX_FLAGS_DEBUG
    "-D_DEBUG -Og"
    CACHE INTERNAL "C++ Compiler options for debug build type")
set(CMAKE_ASM_FLAGS_DEBUG
    "-D_DEBUG"
    CACHE INTERNAL "ASM Compiler options for debug build type")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG
    ""
    CACHE INTERNAL "Linker options for debug build type")

# ~~~
# Options for RELEASE build
# -Os   Optimize for size. -Os enables all -O2 optimizations.
# -flto Runs the standard link-time optimizer.
# ~~~
set(CMAKE_C_FLAGS_RELEASE
    "-Os -flto"
    CACHE INTERNAL "C Compiler options for release build type")
# Disable link time optimization for C++ since we see error due to undefined
# symbols during linking
set(CMAKE_CXX_FLAGS_RELEASE
    "-Os"
    CACHE INTERNAL "C++ Compiler options for release build type")
set(CMAKE_ASM_FLAGS_RELEASE
    ""
    CACHE INTERNAL "ASM Compiler options for release build type")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE
    "-flto"
    CACHE INTERNAL "Linker options for release build type")

# --------------#
# Set compilers #
# --------------#

set(CMAKE_C_COMPILER
    ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT}
    CACHE INTERNAL "C Compiler")
set(CMAKE_CXX_COMPILER
    ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-g++${TOOLCHAIN_EXT}
    CACHE INTERNAL "C++ Compiler")
set(CMAKE_ASM_COMPILER
    ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT}
    CACHE INTERNAL "ASM Compiler")
set(CMAKE_LINKER
    ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc${TOOLCHAIN_EXT}
    CACHE INTERNAL "C Linker")
set(CMAKE_OBJCOPY
    ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-objcopy${TOOLCHAIN_EXT}
    CACHE INTERNAL "C Object Copy")

set(CMAKE_AR "${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gcc-ar${TOOLCHAIN_EXT}")
set(CMAKE_C_ARCHIVE_CREATE "<CMAKE_AR> qcs <TARGET> <LINK_FLAGS> <OBJECTS>")
set(CMAKE_C_ARCHIVE_FINISH true)

set(CMAKE_FIND_ROOT_PATH ${TOOLCHAIN_PATH}/${${TOOLCHAIN}} ${CMAKE_PREFIX_PATH})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

# ---------------------------------#
# Set global variables for targets #
# ---------------------------------#

# ~~~
# Prefix to set map file for an executable. Use this in "target_link_options"
# Example usage:-
#   target_link_options(${EXECUTABLE} PUBLIC ${TOOLCHAIN_SET_EXE_MAP_PREFIX}${EXECUTABLE}.map)
#
# CACHE INTERNAL(CMAKE options):
#   They may be used to store variables persistently across runs.
# ~~~
set(TOOLCHAIN_SET_MAP_PREFIX
    "-Wl,-Map="
    CACHE INTERNAL "Prefix to set map file for the executable")

# ~~~
# Prefix to set the linker script for an executable. Use this in "target_link_options"
# Example usage:-
#   target_link_options(${EXECUTABLE} PUBLIC ${TOOLCHAIN_SET_LINKER_SCRIPT_PREFIX}<path/to/linker/script>)
#
# CACHE INTERNAL(CMAKE options):
#   They may be used to store variables persistently across runs.
# ~~~
set(TOOLCHAIN_SET_LINKER_SCRIPT_PREFIX
    "-T"
    CACHE INTERNAL "Prefix to set linker script for the executable")
