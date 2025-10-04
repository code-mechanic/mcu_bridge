# Example usage:
# make add-repo REPO_URL=https://github.com/STMicroelectronics/STM32CubeG4.git REPO_PATH=external/stm32cube_g4
# make remove-repo REPO_PATH=external/stm32cube_g4

MCU_BRIDGE_MCU ?= stm32g4xx
MCU_BRIDGE_MCU_ID := $(shell echo $(MCU_BRIDGE_MCU) | cut -c6-7)
MCU_BRIDGE_MCU_LOWER := $(shell echo $(MCU_BRIDGE_MCU) | tr 'A-Z' 'a-z')

CMSIS_5_REPO_HTML = https://github.com/ARM-software/CMSIS_5.git
STM32_CMSIS_DEVICE_REPO_HTML = https://github.com/STMicroelectronics/cmsis-device-$(MCU_BRIDGE_MCU_ID).git
STM32_HAL_DRIVER_REPO_HTML = https://github.com/STMicroelectronics/$(MCU_BRIDGE_MCU_LOWER)-hal-driver.git

REPO_FOLDER_NAME = "external"

RESET   := \e[0m
BOLD    := \e[1m
BLACK   := \e[30m
RED     := \e[31m
GREEN   := \e[32m
YELLOW  := \e[33m
BLUE    := \e[34m
MAGENTA := \e[35m
CYAN    := \e[36m
WHITE   := \e[37m

BRIGHT_RED    := \e[91m
BRIGHT_GREEN  := \e[92m
BRIGHT_YELLOW := \e[93m
BRIGHT_BLUE   := \e[94m
BRIGHT_MAGENTA:= \e[95m
BRIGHT_CYAN   := \e[96m
BRIGHT_WHITE  := \e[97m

define git_targets_add_repo
	@git clone --recurse-submodules $(1) $(2)
	@echo "$(BRIGHT_GREEN)Added repo from:$(1) at path:$(2)$(RESET)"
endef

define git_targets_remove_repo
	@rm -rf $(1)
	@echo "$(BRIGHT_GREEN)Removed repo at path:$(1)$(RESET)"
endef

add-repo:
	@if [ -z "$(REPO_URL)" ] || [ -z "$(REPO_PATH)" ]; then \
		echo "Usage: make add-repo REPO_URL=<url> REPO_PATH=<REPO_PATH>"; \
		exit 1; \
	fi
	$(call, git_targets_add_repo, $(REPO_URL) $(REPO_PATH))

remove-repo:
	@if [ -z "$(REPO_PATH)" ]; then \
		echo "Usage: make remove-repo REPO_PATH=<REPO_PATH>"; \
		exit 1; \
	fi
	$(call, git_targets_remove_repo, $(REPO_PATH))

add-stm32-family: validate_mcu
	@if [ -z "$(MCU_BRIDGE_MCU)" ]; then \
		echo "Usage: make add-stm32-family MCU_BRIDGE_MCU=<stm32g4xx>/<stm32g0xx>"; \
		exit 1; \
	fi
	$(call git_targets_add_repo, $(STM32_CMSIS_DEVICE_REPO_HTML), $(REPO_FOLDER_NAME)/stm32/cmsis-device-$(MCU_BRIDGE_MCU_ID))
	$(call git_targets_add_repo, $(STM32_HAL_DRIVER_REPO_HTML), $(REPO_FOLDER_NAME)/stm32/$(MCU_BRIDGE_MCU_LOWER)-hal-driver)
	@echo "$(BRIGHT_YELLOW)NOTE: Make sure CMSIS_5 is added as well by running: make add-cmsis-5 $(RESET)"

remove-stm32-family:
	@if [ -z "$(MCU_BRIDGE_MCU)" ]; then \
		echo "Usage: make remove-stm32-family MCU_BRIDGE_MCU=<stm32g4xx>"; \
		exit 1; \
	fi
	$(call git_targets_remove_repo, $(REPO_FOLDER_NAME)/stm32/cmsis-device-$(MCU_BRIDGE_MCU_ID))
	$(call git_targets_remove_repo, $(REPO_FOLDER_NAME)/stm32/$(MCU_BRIDGE_MCU_LOWER)-hal-driver)

add-cmsis-5:
	$(call git_targets_add_repo, $(CMSIS_5_REPO_HTML), $(REPO_FOLDER_NAME)/CMSIS_5)

validate_mcu:
	@echo "Validating MCU: $(MCU_BRIDGE_MCU)"
	@if [ $$(echo $(MCU_BRIDGE_MCU) | cut -c1-5) != "stm32" ]; then \
		echo "Error: MCU_BRIDGE_MCU must start with 'stm32'"; \
		exit 1; \
	fi
	@if [ $$(echo $(MCU_BRIDGE_MCU) | rev | cut -c1-2 | rev) != "xx" ]; then \
		echo "Error: MCU_BRIDGE_MCU must end with 'xx'"; \
		exit 1; \
	fi
	@if [ $$(echo -n $(MCU_BRIDGE_MCU) | wc -c) -ne 9 ]; then \
		echo "Error: MCU_BRIDGE_MCU must be 9 characters long"; \
		exit 1; \
	fi
	@echo "MCU_BRIDGE_MCU input is valid ✅"
