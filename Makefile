#============================================================================#
#                                 BobEngine                                  #
#============================================================================#

# Compiler and common flags
CXX = g++

# Specific flags for different build profiles
COMMON_CFLAGS = -Wall -fdiagnostics-color=auto -Iinclude
LIBS = -lglfw -lGLEW -lGLU -lGL

# Just a normal thingy
CFLAGS_NORMAL = $(COMMON_CFLAGS) -O2

# For debugging
CFLAGS_DEBUG = $(COMMON_CFLAGS) -Og -g -fstack-protector

# Optimized for release
CFLAGS_RELEASE = $(COMMON_CFLAGS) -O3 -fno-math-errno -fomit-frame-pointer -fno-strict-aliasing \
    -flto -fuse-linker-plugin

# Fast but unstable for release
CFLAGS_FAST = $(COMMON_CFLAGS) -Ofast -march=native -fno-math-errno -fomit-frame-pointer -fno-strict-aliasing \
    -flto -fuse-linker-plugin -fprefetch-loop-arrays -ftree-vectorize

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

#=============================================================================
# Source files and executable
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
SRC := $(wildcard $(SRC_DIR)/*.cpp)
OBJ := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC))
EXECUTABLE := $(BIN_DIR)/main

#=============================================================================
# Default target rule
default: run-debug
.PHONY: default

# Build all
all: normal debug fast release
.PHONY: all

#=============================================================================
# Build target rules
define build_rule
$(1): $(BIN_DIR) $(OBJ_DIR) $$(OBJ)
	$$(CXX) $($(2)) -o $(EXECUTABLE)_$(1) $$(OBJ) $$(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$$(CXX) -c $$< -o $$@

endef

$(foreach target, normal debug fast release, $(eval $(call build_rule,$(target),CFLAGS_$(shell echo $(target) | tr '[:lower:]' '[:upper:]'))))

#=============================================================================
# Run target rules
define run_rule
run-$(1): $(1)
	./$$(EXECUTABLE)_$(1)
endef

$(foreach target, normal debug fast release, $(eval $(call run_rule,$(target))))

.PHONY: run-normal run-debug run-fast run-release

# Run aliases
r: run-debug
run: run-normal
rund: run-debug
runf: run-fast
runr: run-release
.PHONY: r run rund runf runr

#=============================================================================
# Clean rules
define clean_rule
clean-$(1):
	rm -f $$(EXECUTABLE)_$(1)
endef

$(foreach target, normal debug fast release, $(eval $(call clean_rule,$(target))))

clean:
	rm -rf $(BIN_DIR) $(OBJ_DIR)

.PHONY: clean clean-normal clean-debug clean-fast clean-release

#=============================================================================
# Directory creation
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

