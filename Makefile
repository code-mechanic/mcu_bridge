include config/build_config.mk

# Check if PIC_SDK_MCU is one of the supported MCU values
ifeq ($(filter $(PIC_SDK_MCU), $(PIC_SDK_MCU_SUPPORT_LIST)),)
	$(error PIC_SDK_MCU is not a valid value. Expected $(PIC_SDK_MCU_SUPPORT_LIST))
endif

INC_FLAGS = $(addprefix -I, $(INC_PATH))
SRC_FILES = $(foreach path, $(SRC_PATH), $(wildcard $(path)/*.c))
OBJS := $(subst $(SRC_FILES),$(BUILD_PATH),$(SRC_FILES:.c=.p1))
OBJ_FILES := $(notdir $(OBJS))

# Show current build options
.PHONY: showcfg
showcfg:
	@echo
	@echo Current Makefile build config, edit ./config/build_config.mk to change
	@echo
	@echo PIC_SDK_MCU=$(PIC_SDK_MCU)
	@echo PIC_SDK_BUILD_TYPE=$(PIC_SDK_BUILD_TYPE)
	@echo

# Help message
.PHONY: help
help:
	@echo List of source file to be compile
	@echo
	@for src_file in $(SRC_FILES); do \
		echo "$$src_file ..."; \
	done

# Build the SDK
.PHONY: build_sdk
build_sdk: $(BUILD_PATH)
	@for src_file in $(SRC_FILES); do \
		echo "Compiling $$src_file ..."; \
		$(DOCKER) $(CC) $(CFLAGS) $(INC_FLAGS) -c $$src_file -o $(BUILD_PATH)/$$(basename $$src_file .c).p1; \
	done
	@echo Generating Output files ...
	@$(DOCKER) sh -c "cd $(BUILD_PATH) && \
		$(CC) $(CFLAGS) $(INC_FLAGS) $(OBJ_FILES) -o $(PIC_SDK_MCU)"

# Create the build directory if it doesn't exist
$(BUILD_PATH):
	@mkdir -p $(BUILD_PATH)

## Clean the build, for the platform defined by PIC_SDK_MCU
.PHONY: clean
clean:
	@if [ -d $(BUILD_PATH) ]; then \
		$(DOCKER) rm -r $(BUILD_PATH); \
		echo "Removed build folder"; \
	fi

include cmake/docker_targets.mk
include cmake/lint_targets.mk
