include cmake/config_docker.mk

# Build the Docker image
.PHONY: docker_build
docker_build:
	@docker build -t $(DOCKER_PATH) ./docker

# Start the Docker build container and / or update tools
.PHONY: docker_start
docker_start:
	@docker image pull $(DOCKER_PATH)
	@docker inspect $(CONTAINER)$(QUIET) && { docker stop $(CONTAINER)$(QUIET); docker rm $(CONTAINER)$(QUIET); } || echo "Creating $(CONTAINER)"
	@docker run -it -d --name $(CONTAINER) -e "MCU_BRIDGE_BASE=$(ROOT_DIR)" \
		--restart=always --add-host=host.docker.internal:host-gateway \
		-v $(PWD):$(ROOT_DIR) \
		-w $(ROOT_DIR) $(DOCKER_PATH)

# Remove the docker image and container
.PHONY: docker_stop
docker_stop:
	@docker stop $(CONTAINER)$(QUIET)
	@docker rm $(CONTAINER)$(QUIET)
	@docker image rm $(DOCKER_PATH)$(QUIET)

# Open the docker container in interactive mode
.PHONY: docker_interact
docker_interact: docker_start
	@docker exec -it $(CONTAINER) /bin/bash

# Check docker image and container usage
.PHONY: docker_check_usage
docker_check_usage:
	@echo "\e[36mIMAGE LIST:\e[0m"
	@docker image ls
	@echo "\e[36mCONTAINER LIST:\e[0m"
	@docker container ls
	@echo "\e[36mDISK USAGE:\e[0m"
	@docker system df

# Check docker is able to connect with gdb server
.PHONY: docker_check_gdb
docker_check_gdb:
	@docker exec $(CONTAINER) nc -vz host.docker.internal 3333

# Remove unwanted docker usage
.PHONY: docker_prune
docker_prune:
	@docker system prune -a -f

#===============================================================================
# PIC MCU related targets
#===============================================================================
.PHONY: pic_xc8_list_mcu
pic_xc8_list_mcu:
	@$(DOCKER) xc8 --chipinfo

.PHONY: pic_xc8_docs
pic_xc8_docs:
	@if [ ! -d docs ]; then mkdir docs; fi
	@docker cp $(CONTAINER):/opt/microchip/xc8/v2.50/docs ./docs/xc8_docs
