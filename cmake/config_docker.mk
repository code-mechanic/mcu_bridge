DOCKER_IMG        := ghcr.io/code-mechanic/mcu_bridge
DOCKER_VERSION    := latest
DOCKER_PATH       := $(DOCKER_IMG):$(DOCKER_VERSION)
CONTAINER         := mcu_bridge_builder
ROOT_DIR          := /home/mcu_bridge
MCU_BRIDGE_PATH   := $(ROOT_DIR)
QUIET             := >/dev/null 2>&1

# Run commands in the local docker container if not in said container
# On Windows, you must use PowerShell or some environment that supports `which`
# or always run in Docker
ifeq (, $(shell which docker))
  DOCKER :=
else
  DOCKER := docker exec $(CONTAINER)
endif
