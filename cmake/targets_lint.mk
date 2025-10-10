include cmake/config_lint.mk

# lint_cmake is not included here since it looks like there is some instability with cmakelang.
# It behaves differently on various systems for some files.
lint: ## Lint source files
lint: lint_cxx

lint_cxx:
	@echo LINT_CXX_FILES_PATH=$(LINT_CXX_FILES_PATH)
	@$(DOCKER) bash -c " find $(LINT_CXX_FILES_PATH) $(LINT_CXX_FILE_PATTERN) | xargs $(LINT_CXX_CMD)"
	@echo Linting .c/.cpp/.h files complete

lint_cmake:
	@echo LINT_CMAKE_FILES_PATH=$(LINT_CMAKE_FILES_PATH)
	@$(DOCKER) bash -c " find $(LINT_CMAKE_FILES_PATH) $(LINT_CMAKE_FILE_PATTERN) | xargs -r $(LINT_CMAKE_CMD)"
	@echo Linting cmake files complete

# format_cmake is not included here since it looks like there is some instability with cmakelang.
# It behaves differently on various systems for some files.
# Put below comment to turn ON/OFF the formatting in code
# /* clang-format off */
# /* clang-format on */
format: ## Apply consistent formatting to source files
format: format_cxx

format_cxx:
	@echo FORMAT_CXX_FILES_PATH=$(LINT_CXX_FILES_PATH)
	@echo Formatting .c/.cpp/.h files...
	@$(DOCKER) bash -c "find $(LINT_CXX_FILES_PATH) $(LINT_CXX_FILE_PATTERN) | xargs $(FORMAT_CXX_CMD)"
	@echo Restoring local user ownership...
	@$(DOCKER) bash -c "find $(LINT_CXX_FILES_PATH) -user root | xargs -r chown $(UID):$(UID)"
	@echo Formatting .c/.cpp/.h files complete

format_cmake: ## Apply consistent formatting to cmake files
	@echo FORMAT_CMAKE_FILES_PATH=$(LINT_CMAKE_FILES_PATH)
	@echo Formatting cmake files...
	@$(DOCKER) bash -c "find $(LINT_CMAKE_FILES_PATH) $(LINT_CMAKE_FILE_PATTERN) | xargs -r $(FORMAT_CMAKE_CMD)"
	@echo Restoring local user ownership...
	@$(DOCKER) bash -c "find $(LINT_CMAKE_FILES_PATH) -user root | xargs -r chown $(UID):$(UID)"
	@echo Formatting complete

format_python: ## Apply consistent formatting to python files
	@echo FORMAT_PYTHON_FILES_PATH=$(LINT_PYTHON_FILES_PATH)
	@echo Formatting python files...
	@$(DOCKER) bash -c "find $(LINT_PYTHON_FILES_PATH) $(LINT_PYTHON_FILE_PATTERN) | xargs -r $(FORMAT_PYTHON_CMD)"
	@echo Restoring local user ownership...
	@$(DOCKER) bash -c "find $(LINT_PYTHON_FILES_PATH) -user root | xargs -r chown $(UID):$(UID)"
	@echo Formatting complete
