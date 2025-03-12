#-------------#
# Set globals #
#-------------#

# This is the path set in Docker image
LINT_PATH         := /opt/pic_sdk
UID               := $(shell id -u $$USER)

#---------------------------------------#
# C/C++ and Headers Lint Configurations #
#---------------------------------------#

# Add all directories for which linting needs to be enabled.
LINT_CXX_FILES_DIR_LIST := include \
                           source \
                           test \

# Add any subdirectories for which linting needs to be skipped
LINT_CXX_FILES_EXCLUDE_DIR_LIST :=

LINT_CXX_FILE_PATTERN := \( -iname \"*.h\" -or -iname \"*.c\" -or -iname \"*.cpp\" \)

LINT_CXX_FILES_PATH   := $(addprefix ./, $(LINT_CXX_FILES_DIR_LIST)) \
                         $(addprefix ! -path '*/, $(addsuffix /*', $(LINT_CXX_FILES_EXCLUDE_DIR_LIST)))

FORMAT_CXX_CMD        := clang-format -i --style=file:$(LINT_PATH)/.clang-format
LINT_CXX_CMD          := $(FORMAT_CXX_CMD) --dry-run --Werror

#---------------------------#
# CMake Lint Configurations #
#---------------------------#

# Add all directories for which linting needs to be enabled.
LINT_CMAKE_FILES_DIR_LIST := config \
                             source \
                             test \

# Add any subdirectories for which linting needs to be skipped
LINT_CMAKE_FILES_EXCLUDE_DIR_LIST :=

LINT_CMAKE_FILE_PATTERN := \( -iname \"CMakeLists.txt\" -or -iname \"*.cmake\" \)

LINT_CMAKE_FILES_PATH   := $(addprefix ./, $(LINT_CMAKE_FILES_DIR_LIST)) \
                           $(addprefix ! -path '*/, $(addsuffix /*', $(LINT_CMAKE_FILES_EXCLUDE_DIR_LIST)))

FORMAT_CMAKE_CMD        := python3 -m cmakelang.format --tab-size 4 --line-width 110 -i
LINT_CMAKE_CMD          := python3 -m cmakelang.format --tab-size 4 --line-width 110 --check

#----------------------------#
# Python Lint Configurations #
#----------------------------#

# Add all directories for which linting needs to be enabled.
LINT_PYTHON_FILES_DIR_LIST := config \
                              docker \
                              include \
                              internal \
                              source \
                              test \

# Add any subdirectories for which linting needs to be skipped
LINT_PYTHON_FILES_EXCLUDE_DIR_LIST :=

LINT_PYTHON_FILE_PATTERN := \( -iname \"*.py\" \)

LINT_PYTHON_FILES_PATH   := $(addprefix ./, $(LINT_PYTHON_FILES_DIR_LIST)) \
                            $(addprefix ! -path '*/, $(addsuffix /*', $(LINT_PYTHON_FILES_EXCLUDE_DIR_LIST)))

FORMAT_PYTHON_CMD        := python3 -m black
