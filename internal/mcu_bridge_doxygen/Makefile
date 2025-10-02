#
# doxygen.cfg is the default config generated using "doxygen -g doxygen.cfg".
# The only change we do to this file is to include mcu_bridge.cfg as the last line in this file.
# mcu_bridge.cfg is then used to specify project specific config on top of defaults.
#
# Below variables are use inside mcu_bridge.cfg and need to 'export'ed
export MCU_BRIDGE_PATH?=${shell pwd}/../../
export DOXY_DOCS_OUTPUT_PATH=$(MCU_BRIDGE_PATH)/docs/user_guide

PUMLS := $(shell find . -iname "*.puml")
PNGS  := $(PUMLS:.puml=.png)

all: images
	mkdir -p $(DOXY_DOCS_OUTPUT_PATH)
# cp theme/*.png $(DOXY_DOCS_OUTPUT_PATH)/
	@echo Generating doxygen documentation ...
	doxygen doxygen.cfg

.PHONY: images
images: $(PNGS)
	@echo Generating plantuml image files ...

%.png: %.puml
	plantuml $<

clean:
	rm -rf $(DOXY_DOCS_OUTPUT_PATH)
