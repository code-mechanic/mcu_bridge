include config/developement_config.mk
include cmake/config_build.mk

# Check if MCU_BRIDGE_HW is one of the supported values
ifeq ($(filter $(MCU_BRIDGE_HW), $(MCU_BRIDGE_HW_SUPPORT_LIST)),)
	$(error $(MCU_BRIDGE_HW) is not a valid MCU_BRIDGE_HW value. Expected $(MCU_BRIDGE_HW_SUPPORT_LIST))
endif

# ==============================================================================
# Build mcu_bridge, for the platform defined by MCU_BRIDGE_HW
# ==============================================================================
.PHONY: mcu_bridge
mcu_bridge: cmakefiles
	@$(DOCKER) cmake --build $(CMAKE_BUILD_PATH)
	@echo Set local user ownership for ./$(MCU_BRIDGE_BUILD_ROOT)...
	@$(DOCKER) chown -R $(UID):$(UID) ./$(MCU_BRIDGE_BUILD_ROOT)

# ==============================================================================
# Build with debug options, for the platform defined by MCU_BRIDGE_HW
# ==============================================================================
.PHONY: debug
debug:
debug: CMAKE_BUILD_TYPE = "Debug"
debug: mcu_bridge

# ==============================================================================
#  Build with release options, for the platform defined by MCU_BRIDGE_HW
# ==============================================================================
.PHONY: release
release:
release: CMAKE_BUILD_TYPE = "Release"
release: mcu_bridge

# ==============================================================================
# Clean the build, for the platform defined by MCU_BRIDGE_HW
# ==============================================================================
.PHONY: clean
clean:
	@$(DOCKER) rm -rf $(CMAKE_BUILD_PATH)

# ==============================================================================
# Generate cmake files, for the platform defined by MCU_BRIDGE_HW
#
# Edit below options to adjust cmake command line args,
#   - CMAKE_BUILD_PATH        = ./config/build_config.mk
#
#   - CMAKE_BUILD_TYPE        = ./config/development_config.mk
#   - MCU_BRIDGE_HW           = ./config/development_config.mk
#   - MCU_BRIDGE_MCU          = ./config/development_config.mk
#   - MCU_BRIDGE_MCU_VERSION  = ./config/development_config.mk
#   - CMAKE_VERBOSE_MAKEFILE  = ./config/development_config.mk
#
#   - DOCKER_IMG              = ./config/docker_config.mk
#   - TOOLCHAIN_PATH          = ./config/$(MCU_BRIDGE_HW)/$(MCU_BRIDGE_HW)_build_config.mk
#   - MCU_BRIDGE_HW_ADDITIONAL_CMAKE_OPTIONS = ./config/$(MCU_BRIDGE_HW)/$(MCU_BRIDGE_HW)_build_config.mk
#
# Build system generator is "Unix Makefiles"
# ==============================================================================
.PHONY: cmakefiles
cmakefiles:
	@$(DOCKER) cmake -B $(CMAKE_BUILD_PATH) \
				-DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) \
				-DMCU_BRIDGE_HW=$(MCU_BRIDGE_HW) \
				-DMCU_BRIDGE_MCU=$(MCU_BRIDGE_MCU) \
				-DMCU_BRIDGE_MCU_VERSION=$(MCU_BRIDGE_MCU_VERSION) \
				-DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE_MAKEFILE} \
				-DDOCKER_IMG=${DOCKER_IMG} \
				-DTOOLCHAIN_PATH=${TOOLCHAIN_PATH} \
				-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} \
				-DMCU_BRIDGE_EXAMPLE=${MCU_BRIDGE_EXAMPLE} \
				$(MCU_BRIDGE_HW_ADDITIONAL_CMAKE_OPTIONS) \
				--graphviz=$(CMAKE_BUILD_PATH)/cmake_graph.dot \
				-G "Unix Makefiles"
ifneq (, $(DOT))
	-@$(DOCKER) dot -Tpng -o $(CMAKE_BUILD_PATH)/cmake_graph.png $(CMAKE_BUILD_PATH)/cmake_graph.dot
endif

# ==============================================================================
# Other targets
# ==============================================================================
include cmake/targets_docker.mk
include cmake/targets_lint.mk
include cmake/targets_docs.mk
include cmake/targets_git.mk

# ==============================================================================
# Build mcu_bridge, for the platform defined by MCU_BRIDGE_HW and lint and generate docs
# ==============================================================================
.PHONY: mcu_bridge_all
mcu_bridge_all:
	$(MAKE) lint
	$(MAKE) docs
	$(MAKE) debug
	$(MAKE) release

# ==============================================================================
# Clean the build and docs
# ==============================================================================
.PHONY: clean_all
clean_all:
	$(MAKE) clean
	$(MAKE) docs-clean
