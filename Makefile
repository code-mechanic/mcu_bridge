include config/docker_config.mk
include config/build_config.mk

# Check if PIC_SDK_MCU is one of the supported MCU values
ifeq ($(filter $(PIC_SDK_MCU), $(PIC_SDK_MCU_SUPPORT_LIST)),)
	$(error PIC_SDK_MCU is not a valid value. Expected $(PIC_SDK_MCU_SUPPORT_LIST))
endif

INC_FLAGS = $(addprefix -I, $(INC_PATH))
SRC_FILES = $(foreach path, $(SRC_PATH), $(wildcard $(path)/*.c))
OBJS := $(subst $(SRC_FILES),$(BUILD_PATH),$(SRC_FILES:.c=.p1))
OBJ_FILES := $(notdir $(OBJS))

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

# Build the Docker image
.PHONY: docker_build
docker_build:
	@docker build -t $(DOCKER_PATH) ./docker

# Start the Docker build container and / or update tools
.PHONY: docker_start
docker_start:
	@docker image pull $(DOCKER_PATH)
	@docker inspect $(CONTAINER)$(QUIET) && { docker stop $(CONTAINER)$(QUIET); docker rm $(CONTAINER)$(QUIET); } || echo "Creating $(CONTAINER)"
	@docker run -it -d --name $(CONTAINER) -e "PIC_SDK_BASE=$(ROOT_DIR)" \
		--restart=always --add-host=host.docker.internal:host-gateway \
		-v $(PWD):$(ROOT_DIR) \
		-w $(ROOT_DIR) $(DOCKER_PATH)

# Remove the docker image and container
.PHONY: docker_stop
docker_stop:
	@docker stop $(CONTAINER)$(QUIET)
	@docker rm $(CONTAINER)$(QUIET)
	@docker image rm $(DOCKER_PATH)$(QUIET)

# Check docker image and container
.PHONY: docker_check
docker_check:
	@echo "\e[36mIMAGE LIST:\e[0m"
	@docker image ls
	@echo "\e[36mCONTAINER LIST:\e[0m"
	@docker container ls

# Show current build options
.PHONY: showcfg
showcfg:
	@echo
	@echo Current Makefile build config, edit ./make_config/build_config.mk to change
	@echo
	@echo PIC_SDK_MCU=$(PIC_SDK_MCU)
	@echo PIC_SDK_BUILD_TYPE=$(PIC_SDK_BUILD_TYPE)
	@echo

## Clean the build, for the platform defined by PIC_SDK_MCU
.PHONY: clean
clean:
	@if [ -d $(BUILD_PATH) ]; then \
		$(DOCKER) rm -r $(BUILD_PATH); \
		echo "Removed build folder"; \
	fi