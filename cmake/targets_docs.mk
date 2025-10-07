.PHONY: docs
docs: ## Generate docs
	@$(DOCKER) bash -c "make -C internal/mcu_bridge_doxygen"
	@$(DOCKER) bash -c "plantuml ./internal/**/*.uml"
	@$(DOCKER) bash -c "plantuml ./internal/**/*.puml"
	@echo Documentation generation complete

docs-clean: ## Remove generated docs
	@$(DOCKER) bash -c "make -s -C internal/mcu_bridge_doxygen clean"
