# Example usage:
# make add-repo REPO_URL=https://github.com/STMicroelectronics/STM32CubeG4.git REPO_PATH=external/stm32cube_g4
# make remove-repo REPO_PATH=external/stm32cube_g4

MCU_BRIDGE_MCU ?= stm32g4xx
MCU_BRIDGE_MCU_ID := $(shell echo $(MCU_BRIDGE_MCU) | cut -c6-7)
MCU_BRIDGE_MCU_LOWER := $(shell echo $(MCU_BRIDGE_MCU) | tr 'A-Z' 'a-z')

CMSIS_5_REPO_HTML = https://github.com/ARM-software/CMSIS_5.git
CMSIS_5_DEST_PATH = external/CMSIS_5

STM32_CMSIS_DEVICE_REPO_HTML = https://github.com/STMicroelectronics/cmsis-device-$(MCU_BRIDGE_MCU_ID).git
STM32_CMSIS_DEVICE_DEST_PATH = external/stm32/cmsis_device_$(MCU_BRIDGE_MCU_ID)

STM32_HAL_DRIVER_REPO_HTML = https://github.com/STMicroelectronics/$(MCU_BRIDGE_MCU_LOWER)-hal-driver.git
STM32_HAL_DRIVER_DEST_PATH = external/stm32/$(MCU_BRIDGE_MCU_LOWER)_hal_driver

STM32_HAL_DRIVER_CONFIG_TEMPLATE = external/stm32/$(MCU_BRIDGE_MCU_LOWER)_hal_driver/Inc/$(MCU_BRIDGE_MCU_LOWER)_hal_conf_template.h
STM32_HAL_DRIVER_CONFIG_DEST_PATH = config/stm32/$(MCU_BRIDGE_MCU_LOWER)_hal_conf.h

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

.PHONY: git-targets-help
git-targets-help:
	@echo "Available git targets:"
	@echo "  make add-repo            REPO_URL=<url>   REPO_PATH=<path>      - Clone a git repository into the specified path"
	@echo "  make remove-repo         REPO_PATH=<path>                       - Remove the specified repository path"
	@echo "  make add-stm32-family    MCU_BRIDGE_MCU=<stm32g4xx>/<stm32g0xx> - Add STM32 family repositories"
	@echo "  make remove-stm32-family MCU_BRIDGE_MCU=<stm32g4xx>/<stm32g0xx> - Remove STM32 family repositories"
	@echo "  make add-cmsis-5                                                - Add CMSIS_5 repository"

.PHONY: add-repo
add-repo:
	@if [ -z "$(REPO_URL)" ] || [ -z "$(REPO_PATH)" ]; then \
		echo "Usage: make add-repo REPO_URL=<url> REPO_PATH=<REPO_PATH>"; \
		exit 1; \
	fi
	@git clone --recurse-submodules $(REPO_URL) $(REPO_PATH)
	@echo "$(BRIGHT_GREEN)Added repo from:$(REPO_URL) at path:$(REPO_PATH)$(RESET)"

.PHONY: remove-repo
remove-repo:
	@if [ -z "$(REPO_PATH)" ]; then \
		echo "Usage: make remove-repo REPO_PATH=<REPO_PATH>"; \
		exit 1; \
	fi
	@rm -rf $(REPO_PATH)
	@echo "$(BRIGHT_GREEN)Removed repo at path:$(REPO_PATH)$(RESET)"

.PHONY: add-stm32-family
add-stm32-family: validate_mcu
	@if [ -z "$(MCU_BRIDGE_MCU)" ]; then \
		echo "Usage: make add-stm32-family MCU_BRIDGE_MCU=<stm32g4xx>/<stm32g0xx>"; \
		exit 1; \
	fi

	@if [ -d "$(STM32_CMSIS_DEVICE_DEST_PATH)" ]; then \
		echo "$(BRIGHT_RED)Directory $(STM32_CMSIS_DEVICE_DEST_PATH) already exists. Skipping cloning $(RESET)"; \
	else \
		git clone --recurse-submodules $(STM32_CMSIS_DEVICE_REPO_HTML) $(STM32_CMSIS_DEVICE_DEST_PATH); \
		echo "$(BRIGHT_GREEN)Added repo from:$(STM32_CMSIS_DEVICE_REPO_HTML) at path:$(RESET) $(STM32_CMSIS_DEVICE_DEST_PATH)"; \
	fi

	@if [ -d "$(STM32_HAL_DRIVER_DEST_PATH)" ]; then \
		echo "$(BRIGHT_RED)Directory $(STM32_HAL_DRIVER_DEST_PATH) already exists. Skipping cloning $(RESET)"; \
	else \
		git clone --recurse-submodules $(STM32_HAL_DRIVER_REPO_HTML) $(STM32_HAL_DRIVER_DEST_PATH); \
		echo "$(BRIGHT_GREEN)Added repo from:$(STM32_HAL_DRIVER_REPO_HTML) at path:$(RESET) $(STM32_HAL_DRIVER_DEST_PATH)"; \
		cp $(STM32_HAL_DRIVER_CONFIG_TEMPLATE) $(STM32_HAL_DRIVER_CONFIG_DEST_PATH); \
		echo "$(BRIGHT_GREEN)Copied $(MCU_BRIDGE_MCU) HAL config template to:$(RESET) $(STM32_HAL_DRIVER_CONFIG_DEST_PATH)"; \
		echo "$(BRIGHT_YELLOW)Please update the $(MCU_BRIDGE_MCU) HAL config file as per your requirements.$(RESET)"; \
	fi

	@echo "$(BRIGHT_YELLOW)NOTE: Make sure CMSIS_5 is added as well by running: make add-cmsis-5 $(RESET)"

.PHONY: remove-stm32-family
remove-stm32-family:
	@if [ -z "$(MCU_BRIDGE_MCU)" ]; then \
		echo "Usage: make remove-stm32-family MCU_BRIDGE_MCU=<stm32g4xx>"; \
		exit 1; \
	fi

	@rm -rf $(STM32_CMSIS_DEVICE_DEST_PATH)
	@echo "$(BRIGHT_GREEN)Removed repo at path:$(RESET) $(STM32_CMSIS_DEVICE_DEST_PATH)"

	@rm -rf $(STM32_HAL_DRIVER_DEST_PATH)
	@echo "$(BRIGHT_GREEN)Removed repo at path:$(RESET) $(STM32_HAL_DRIVER_DEST_PATH)"

	@rm -f $(STM32_HAL_DRIVER_CONFIG_DEST_PATH)
	@echo "$(BRIGHT_GREEN)Removed $(MCU_BRIDGE_MCU) HAL config file at path:$(RESET) $(STM32_HAL_DRIVER_CONFIG_DEST_PATH)"

.PHONY: add-cmsis-5
add-cmsis-5:
	@if [ -d "$(CMSIS_5_DEST_PATH)" ]; then \
		echo "$(BRIGHT_RED)Directory $(CMSIS_5_DEST_PATH) already exists. Skipping cloning $(RESET)"; \
	else \
		git clone --recurse-submodules $(CMSIS_5_REPO_HTML) $(CMSIS_5_DEST_PATH); \
		echo "$(BRIGHT_GREEN)Added repo from:$(CMSIS_5_REPO_HTML) at path:$(CMSIS_5_DEST_PATH)$(RESET)"; \
	fi

.PHONY: validate_mcu
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
