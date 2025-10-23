
- [How to write Toolchain file for Microcontrollers.](#how-to-write-toolchain-file-for-microcontrollers)
- [General Understanding about Cmake](#general-understanding-about-cmake)
- [Order of CMake execution](#order-of-cmake-execution)
  - [Configuration Phase](#configuration-phase)
  - [Generation Phase](#generation-phase)
  - [Build Phase](#build-phase)
  - [Install Phase (Optional)](#install-phase-optional)
  - [Testing Phase (Optional)](#testing-phase-optional)
- [Before Cmakelists.txt is it possible to process another cmake file?](#before-cmakeliststxt-is-it-possible-to-process-another-cmake-file)
  - [Using a Toolchain File (CMAKE\_TOOLCHAIN\_FILE)](#using-a-toolchain-file-cmake_toolchain_file)
  - [Using the CMAKE\_PROJECT\_INCLUDE Variable](#using-the-cmake_project_include-variable)
  - [Including a CMake Script via Environment Variable](#including-a-cmake-script-via-environment-variable)
  - [Conclusion](#conclusion)
- [Indepth details about cross-compilation.](#indepth-details-about-cross-compilation)

# How to write Toolchain file for Microcontrollers.

Refer https://cmake.org/cmake/help/book/mastering-cmake/chapter/Cross%20Compiling%20With%20CMake.html#cross-compiling-for-a-microcontroller
- The `--trace` option enables verbose output from CMake, showing each command that is executed during the configuration phase. This can be very helpful for understanding the flow of your script.
    - exmaple `cmake -B build/` - This is configuration phase.
- The `--debug-output` option, on the other hand, provides more detailed information about the configuration process. It shows which files are being processed, which commands are being executed, and the values of variables at each step.

# General Understanding about Cmake
- where ever you create a `CMakeLists.txt` then there will be `CMakeFiles` folder present in build directory.

| CMAKE Variable          | Description                                                                                |
|-------------------------|--------------------------------------------------------------------------------------------|
|CMAKE_CURRENT_FUNCTION   | Function name that currently being processed.                                              |
|CMAKE_CURRENT_LIST_DIR   | Full directory of the listfile(*.cmake or CMakeLists.txt) currently being processed.       |
|CMAKE_CURRENT_LIST_FILE  | Full file Path of the listfile(*.cmake or CMakeLists.txt) currently being processed.       |
|CMAKE_CURRENT_LIST_LINE  | Line number of the listfile(*.cmake or CMakeLists.txt) currently being processed.          |
|CMAKE_CURRENT_BINARY_DIR | Represents the binary directory corresponding to the current source directory.             |
|CMAKE_CURRENT_SOURCE_DIR | This is the full path to the source directory that is currently being processed by cmake.  |
|CMAKE_MODULE_PATH        | Adding the directory to the CMAKE_MODULE_PATH simplifies loading various *.cmake files     |
|CMAKE_SYSTEM_NAME        | If explicilty set, then cross-compilation will enable.                                     |
|CMAKE_SYSTEM_PROCESSOR   | In Cross-compilation this is just the user defined value used for developer use            |

# Order of CMake execution

In CMake, the execution order follows a structured sequence, typically divided into

1. Configuration,
2. generation, and
3. build phases.

Here's the general order of execution:

## Configuration Phase
The process starts when you run `cmake ..` inside the build directory.

- `CMakeLists.txt Parsing`: CMake reads the CMakeLists.txt files in a hierarchical manner (from the root directory and then in subdirectories).

- `Processing Commands`: project(), cmake_minimum_required(), set(), option(), and other commands defining variables and options are processed first.

- `Finding Dependencies`: Calls like find_package(), find_library(), include(), and add_subdirectory() are executed.

- `Target Definition`: Commands like add_executable(), add_library(), target_include_directories(), and target_compile_options() define build targets.

## Generation Phase
Once configuration is successful, CMake generates the necessary build system files for the specified generator (e.g., Makefiles, Ninja files, Visual Studio project files, etc.). It resolves dependencies, computes compiler and linker flags, and prepares build commands.

## Build Phase
Initiated by running `cmake --build .` or using make, ninja, or another build system.

The generated build system compiles and links the code according to the defined targets.

Any custom build steps (add_custom_command() or add_custom_target()) are executed.

## Install Phase (Optional)
If an `install()` command is defined in CMakeLists.txt, running `cmake --install .` installs the built artifacts (e.g., binaries, libraries, headers).

## Testing Phase (Optional)
If `enable_testing()` and `add_test()` are used, running ctest executes the defined tests.


# Before Cmakelists.txt is it possible to process another cmake file?

Yes, it is possible to process another CMake file before CMakeLists.txt using the following methods:

## Using a Toolchain File (CMAKE_TOOLCHAIN_FILE)
This is typically used for cross-compilation (e.g., ARM, embedded development).
The toolchain file is processed before CMakeLists.txt.

Example usage:
`cmake -DCMAKE_TOOLCHAIN_FILE=path/to/toolchain.cmake -B build`

Example toolchain.cmake:
```
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)
```

## Using the CMAKE_PROJECT_INCLUDE Variable
This variable can specify a CMake script to be included before project() in CMakeLists.txt.

Usage:
`cmake -DCMAKE_PROJECT_INCLUDE=pre_configure.cmake -B build`

Example pre_configure.cmake:
```
message(STATUS "Pre-configure script executed!")
set(MY_GLOBAL_VAR "Hello from pre-configure script")
```

## Including a CMake Script via Environment Variable
The environment variable CMAKE_PROJECT_INCLUDE_BEFORE allows running a script before CMakeLists.txt execution.

Example:
```
export CMAKE_PROJECT_INCLUDE_BEFORE=pre_setup.cmake
cmake -B build
```

Example pre_setup.cmake:
```
message(STATUS "Running pre-setup script!")
set(PRE_DEFINED_VAR "Configured Before CMakeLists.txt")
```

## Conclusion
Yes, it is possible to process another CMake file before CMakeLists.txt using:

1. Toolchain file (CMAKE_TOOLCHAIN_FILE) – for cross-compilation.
2. CMAKE_PROJECT_INCLUDE – for injecting a pre-processing script.
3. CMAKE_PROJECT_INCLUDE_BEFORE environment variable – for globally setting pre-scripts.

# Indepth details about cross-compilation.

1. `CMAKE_SYSTEM_NAME`
    - The name of the operating system for which CMake is to build.
    - For embedded system, this can be user defined string
        - Example: `set(CMAKE_SYSTEM_NAME "MicrochipMCU")`
    - `CMAKE_CROSSCOMPILING` variable will be set to true by CMake if the `CMAKE_SYSTEM_NAME` variable has been set manually (i.e. in a toolchain file). we can find this variable inside `/build/CMakeFiles/3.23.5/CMakeSystem.cmake`

2. Where our toolchain file get called?
    - build/CMakeFiles/3.23.5/CMakeSystem.cmake