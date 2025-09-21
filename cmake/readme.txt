Q. Order of CMake execution

In CMake, the execution order follows a structured sequence, typically divided into

Configuration,
generation, and
build phases.

Here's the general order of execution:

1. Configuration Phase
The process starts when you run "cmake .." inside the build directory.

    - CMakeLists.txt Parsing: CMake reads the CMakeLists.txt files in a hierarchical manner (from the root directory and then in subdirectories).
    - Processing Commands: project(), cmake_minimum_required(), set(), option(), and other commands defining variables and options are processed first.
    - Finding Dependencies: Calls like find_package(), find_library(), include(), and add_subdirectory() are executed.
    - Target Definition: Commands like add_executable(), add_library(), target_include_directories(), and target_compile_options() define build targets.

2. Generation Phase
Once configuration is successful, CMake generates the necessary build system files for the specified generator (e.g., Makefiles, Ninja files, Visual Studio project files, etc.).

It resolves dependencies, computes compiler and linker flags, and prepares build commands.

3. Build Phase
Initiated by running "cmake --build ." or using make, ninja, or another build system.

The generated build system compiles and links the code according to the defined targets.

Any custom build steps (add_custom_command() or add_custom_target()) are executed.

4. Install Phase (Optional)
If an install() command is defined in CMakeLists.txt, running cmake --install . installs the built artifacts (e.g., binaries, libraries, headers).

5. Testing Phase (Optional)
If enable_testing() and add_test() are used, running ctest executes the defined tests.

================================================================================

Q. Before Cmakelists.txt  is it possible to process another cmake file?

Yes, it is possible to process another CMake file before CMakeLists.txt using the following methods:

1. Using a Toolchain File (CMAKE_TOOLCHAIN_FILE)
This is typically used for cross-compilation (e.g., ARM, embedded development).
The toolchain file is processed before CMakeLists.txt.

Example usage:
cmake -DCMAKE_TOOLCHAIN_FILE=path/to/toolchain.cmake -B build

Example toolchain.cmake:
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER arm-none-eabi-gcc)
set(CMAKE_CXX_COMPILER arm-none-eabi-g++)

2. Using the CMAKE_PROJECT_INCLUDE Variable
This variable can specify a CMake script to be included before project() in CMakeLists.txt.

Usage:
cmake -DCMAKE_PROJECT_INCLUDE=pre_configure.cmake -B build

Example pre_configure.cmake:
message(STATUS "Pre-configure script executed!")
set(MY_GLOBAL_VAR "Hello from pre-configure script")

3. Including a CMake Script via Environment Variable
The environment variable CMAKE_PROJECT_INCLUDE_BEFORE allows running a script before CMakeLists.txt execution.

Example:
export CMAKE_PROJECT_INCLUDE_BEFORE=pre_setup.cmake
cmake -B build

Example pre_setup.cmake:
message(STATUS "Running pre-setup script!")
set(PRE_DEFINED_VAR "Configured Before CMakeLists.txt")

Conclusion
Yes, it is possible to process another CMake file before CMakeLists.txt using:

1. Toolchain file (CMAKE_TOOLCHAIN_FILE) – for cross-compilation.
2. CMAKE_PROJECT_INCLUDE – for injecting a pre-processing script.
3. CMAKE_PROJECT_INCLUDE_BEFORE environment variable – for globally setting pre-scripts.

================================================================================