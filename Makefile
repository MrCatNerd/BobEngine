BUILD_DIR := build

EXECUTABLE_NAME := BobEngine

# Build profile
PROFILE ?= Debug

#########

default: run
.PHONY: default

all: compile compile_commands.json
.PHONY: all

run: compile
	./$(BUILD_DIR)/$(PROFILE)/bin/$(EXECUTABLE_NAME)
.PHONY: run

compile: build
	cmake -B $(BUILD_DIR) -S . -DCMAKE_BUILD_TYPE=$(PROFILE)
	cmake --build $(BUILD_DIR)
.PHONY: compile

clean:
	rm -f $(EXECUTABLE_NAME)
	rm -rf $(BUILD_DIR)
	rm -f CMakeCache.txt
	rm -rf .cache
	rm -f compile_commands.json
.PHONY: clean

compile_commands.json: build
	cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B build -S .
	cp build/compile_commands.json .

build:
	@mkdir -p $(BUILD_DIR)

