DOCKER_IMG        := ghcr.io/code-mechanic/pic_sdk
DOCKER_VERSION    := latest
DOCKER_PATH       := $(DOCKER_IMG):$(DOCKER_VERSION)
CONTAINER         := pic_sdk_builder
ROOT_DIR          := /home/pic_sdk
PIC_SDK_PATH      := $(ROOT_DIR)
QUIET             := >/dev/null 2>&1

# Run commands in the local docker container if not in said container
# On Windows, you must use PowerShell or some environment that supports `which`
# or always run in Docker
ifeq (, $(shell which docker))
  DOCKER :=
else
  DOCKER := docker exec $(CONTAINER)
endif
