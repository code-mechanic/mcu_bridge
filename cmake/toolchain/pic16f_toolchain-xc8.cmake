set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR pic16)

# Set the XC8 compiler path
set(CMAKE_C_COMPILER "/opt/microchip/xc8/v2.50/bin/xc8")
set(CMAKE_ASM_COMPILER "${CMAKE_C_COMPILER}")

# Ensure the compiler is not checked for executables
set(CMAKE_EXECUTABLE_SUFFIX ".hex")
set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_CXX_COMPILER_WORKS 1)

# Avoid compiler ABI checks (XC8 does not produce standard executables)
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

# Force compiler identification to XC8
set(CMAKE_C_COMPILER_ID_RUN TRUE)
set(CMAKE_C_COMPILER_ID "XC8")

# Compiler flags
set(CMAKE_C_FLAGS "--chip=16F877A --opt=default -Wall" CACHE STRING "" FORCE)
set(CMAKE_ASM_FLAGS "${CMAKE_C_FLAGS}" CACHE STRING "" FORCE)

# Set CMake to ignore standard libraries
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE NEVER)
