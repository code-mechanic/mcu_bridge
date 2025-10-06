# ---------------------------------------------------------------##
# CMake arm-none-eabi toolchain file for STM32 series processors ##
# ---------------------------------------------------------------##

# Append current directory to CMAKE_MODULE_PATH for making device specific cmake
# modules visible
#
# ~~~
# CMAKE_MODULE_PATH (CMAKE variable):
#   It is a list of directories where CMake searches for custom modules (.cmake files).
#   These modules are usually used with find_package() or include() commands to locate
#   packages or load additional functionality.
#
# CMAKE_CURRENT_LIST_DIR (CMAKE variable):
#   This variable holds the directory of the currently processed
#   CMake script (CMakeLists.txt or a .cmake file).
# ~~~
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR})

# ------------------#
# Target definition #
# ------------------#

# ~~~
# CMAKE_SYSTEM_NAME (CMAKE variable):
#   The name of the operating system for which CMake is to build. Here it is set
#   to bare metal embedded devices
# ~~~
set(CMAKE_SYSTEM_NAME Generic)
# ~~~
# CMAKE_SYSTEM_PROCESSOR (CMAKE variable):
#   Represents the target CPU architecture. When cross-compiling,
#   a CMAKE_TOOLCHAIN_FILE should set the CMAKE_SYSTEM_PROCESSOR variable to
#   match target architecture
# ~~~
set(CMAKE_SYSTEM_PROCESSOR ARM)

# -----------------------------------#
# Set toolchain paths and extensions #
# -----------------------------------#

# ~~~
# TOOLCHAIN (User defined variable):
#   This variable holds the name of the toolchain
# ~~~
set(TOOLCHAIN arm-none-eabi)

# ~~~
# This toolchain cmake file will be used by CMake multiple times.
# Here, an argument passed would go out of scope. To prevent this,
# append the argument to CMAKE_TRY_COMPILE_PLATFORM_VARIABLES
#
# CMAKE_TRY_COMPILE_PLATFORM_VARIABLES (CMAKE variable):
#    It has a list of environment variables that should be passed when running
#    try_compile() and try_run() commands. These commands are used by CMake to
#    check whether certain code can compile or run on the target system.
# NOTE:
#   DOCKER_IMG and TOOLCHAIN_PATH are passed as cmd line arg usind `-D`
#   in top level Makefile
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
    #
    # ~~~
    # file(TO_CMAKE_PATH <input> <output>)
    #   Converts a given path (<input>) into a format that is compatible with CMake
    #   and Stores the converted path in <output>.
    # ~~~
    file(TO_CMAKE_PATH "$ENV{GCC_ARM_NONE_EABI_PATH}" TOOLCHAIN_PATH)
    if(NOT EXISTS ${TOOLCHAIN_PATH})
      message(
        FATAL_ERROR
          "Toolchain path doesn't exist!! \nSet 'GCC_ARM_NONE_EABI_PATH' env variable!!"
      )
    endif()
  endif()
endif()

# ~~~
# User defined variable
# ~~~
set(TOOLCHAIN_BIN_DIR ${TOOLCHAIN_PATH}/bin)
set(TOOLCHAIN_INC_DIR ${TOOLCHAIN_PATH}/${TOOLCHAIN}/include)
set(TOOLCHAIN_LIB_DIR ${TOOLCHAIN_PATH}/${TOOLCHAIN}/lib)

set(TOOLCHAIN_EXT "")
# ~~~
# CMAKE_HOST_SYSTEM_NAME (CMAKE variable):
#   Name of the OS CMake is running on.
# ~~~
if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL Windows)
  set(TOOLCHAIN_EXT ".exe")
endif()

# Perform compiler test with static library
#
# ~~~
# CMAKE_TRY_COMPILE_TARGET_TYPE (CMAKE variable):
#   By default, when CMake uses try_compile(), it tries to build an executable 
#   to test compiler and system capabilities. However, in cross-compilation scenarios,
#   running an executable on the build machine may not be possible (e.g., compiling for an embedded target).
#   To avoid this issue, we can change CMAKE_TRY_COMPILE_TARGET_TYPE to STATIC_LIBRARY,
#   so that CMake only checks for successful compilation and does not require linking or running the binary
# ~~~
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# --------------------------------#
# Set local Compiler/Linker Flags #
# --------------------------------#

# ~~~
# STM32 MCU specific flags
# -mcpu                 Build for Arm v7-m Cortex-M4
# -mthumb               Use the thumb instruction set
# -mfpu=fpv4-sp-d16     VFPv4 single precision FPU
# -mfloat-abi=hard      Use floating point instructions and the floating point ABI
#
# User defined variable
# ~~~
set(STM32_MCU_FLAGS 
    "-mcpu=cortex-m4 -mthumb"
)

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
#
# User defined variable
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
#
# CMAKE_C_FLAGS (CMAKE variable):
#   C compiler flags to be used to create executables. These flags will be used by
#   the C compiler when creating an executable.
# ~~~
set(CMAKE_C_FLAGS
    "${STM32_MCU_FLAGS} ${OBJECT_GEN_FLAGS} -std=gnu99 "
    CACHE INTERNAL "C Compiler options")

# ~~~
# C++ Flags
# -std=c++17            Follow the C++ 17 Standard
#
# CMAKE_CXX_FLAGS (CMAKE variable):
#   C++ compiler flags to be used to create executables. These flags will be used by
#   the C++ compiler when creating an executable.
# ~~~
set(CMAKE_CXX_FLAGS
    "${STM32_MCU_FLAGS} ${OBJECT_GEN_FLAGS} -std=c++17 -fno-rtti -fno-exceptions -fno-threadsafe-statics -fno-unwind-tables -fmessage-length=0 -funsigned-char"
    CACHE INTERNAL "C++ Compiler options")

# ~~~
# ASM Flags
# -x assembler-with-cpp Allow C directives in assembly files
#
# CMAKE_ASM_FLAGS (CMAKE variable):
#   Assembler flags to be used to create executables. These flags will be used by
#   the assembler when creating an executable.
# ~~~
set(CMAKE_ASM_FLAGS
    "${STM32_MCU_FLAGS} ${OBJECT_GEN_FLAGS} -x assembler-with-cpp "
    CACHE INTERNAL "ASM Compiler options")

# ~~~
# Linker Flags
# --specs=nano.specs    Link with newlib-nano.
# --specs=nosys.specs   No syscalls, provide empty implementations for the POSIX system calls.
# -Wl,-Map              Generate a map file
# -Wl,--gc-sections     Perform the dead code elimination.
#
# CMAKE_EXE_LINKER_FLAGS (CMAKE variable):
#   Linker flags to be used to create executables. These flags will be used by
#   the linker when creating an executable.
# ~~~
set(CMAKE_EXE_LINKER_FLAGS
    "${STM32_MCU_FLAGS} --specs=nano.specs --specs=nosys.specs -Wl,--gc-sections -Wl,--print-memory-usage"
    CACHE INTERNAL "Linker options")

# ----------------------------------------------#
# Set debug/release build configuration Options #
# ----------------------------------------------#

# ~~~
# Options for DEBUG build
# -Og                   Enables optimizations that do not interfere with debugging
# -Wno-unused-variable  May be temporarily unused during debugging
# -Wno-unused-function  May be temporarily unused during debugging
#
# CMAKE_<LANG>_FLAGS_DEBUG (CMAKE variable):
#   Compiler flags to be used to create executables for the debug build type.
#   It is applied only when CMAKE_BUILD_TYPE is set to Debug
# CMAKE_EXE_LINKER_FLAGS_<CONFIG> (CMAKE variable):
#   Linker flags to be used to create executables for the debug build type.
# ~~~
set(CMAKE_C_FLAGS_DEBUG
    "-D_DEBUG -Og -Wno-unused-variable -Wno-unused-function"
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
#
# CMAKE_<LANG>_FLAGS_RELEASE (CMAKE variable):
#   Compiler flags to be used to create executables for the release build type.
#   It is applied only when CMAKE_BUILD_TYPE is set to release
# CMAKE_EXE_LINKER_FLAGS_<CONFIG> (CMAKE variable):
#   Linker flags to be used to create executables for the release build type.
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

# ~~~
# Options for RELEASE build
# -Os   Optimize for size. -Os enables all -O2 optimizations.
# -flto Runs the standard link-time optimizer.
#
# CMAKE_<LANG>_COMPILER (CMAKE variable):
#   Path to the compilers
# CMAKE_LINKER (User defined variable):
#   Path to the linker
# CMAKE_OBJCOPY (User defined variable):
#   Path to utility
# CMAKE_AR (CMAKE variable):
#   Name of archiving tool for static libraries.
# CMAKE_C_ARCHIVE_CREATE (CMAKE variable):
#   This is a rule variable that tells CMake how to create a static archive
# CMAKE_C_ARCHIVE_FINISH (CMAKE variable):
#   This is a rule variable that tells CMake how to finish a static archive
# CMAKE_FIND_ROOT_PATH (CMAKE variable):
#   Semicolon-separated list of root paths to search on the filesystem
# CMAKE_PREFIX_PATH (CMAKE variable):
#   Semicolon-separated list of directories specifying installation prefixes
#   to be searched by the find_package(), find_program(), find_library(),
#   find_file(), and find_path() commands
# CMAKE_FIND_ROOT_PATH_MODE_PROGRAM (CMAKE variable):
# CMAKE_FIND_ROOT_PATH_MODE_LIBRARY (CMAKE variable):
# CMAKE_FIND_ROOT_PATH_MODE_INCLUDE (CMAKE variable):
# CMAKE_FIND_ROOT_PATH_MODE_PACKAGE (CMAKE variable):
# ~~~
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
# User defined variable
# ~~~
set(TOOLCHAIN_SET_MAP_PREFIX
    "-Wl,-Map="
    CACHE INTERNAL "Prefix to set map file for the executable")

# ~~~
# Prefix to set the linker script for an executable. Use this in "target_link_options"
# Example usage:-
#   target_link_options(${EXECUTABLE} PUBLIC ${TOOLCHAIN_SET_LINKER_SCRIPT_PREFIX}<path/to/linker/script>)
#
# User defined variable
# ~~~
set(TOOLCHAIN_SET_LINKER_SCRIPT_PREFIX
    "-T"
    CACHE INTERNAL "Prefix to set linker script for the executable")
