CXX ?= g++

# path #
SRC_PATH = src
BUILD_PATH = build
BIN_PATH = $(BUILD_PATH)/bin
MAIN_PATH = main

# extensions #
SRC_EXT = cpp

# code lists #
# Find all source files in the source directory, sorted by
# most recently modified
SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
MAINS = $(shell find $(MAIN_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
#Set main files .cpp to create binaries
BINARIES = $(MAINS:$(MAIN_PATH)/%.$(SRC_EXT)=$(BIN_PATH)/%)
# Set the dependency files that will be used to add header dependencies
DEPS = $(OBJECTS:.o=.d)

# flags #
COMPILE_FLAGS = -O3 -std=c++20 -DLOCAL -g
INCLUDES = -I include/ -I /usr/local/include
# Space-separated pkg-config libraries used by this project
LIBS =

.PHONY: default_target
default_target: release

.PHONY: release
release: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS)
release: dirs
	@echo $(BINARIES)
	@$(MAKE) all

.PHONY: dirs
dirs:
	@echo "Creating directories"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)

.PHONY: clean
clean:
	@echo "Deleting directories"
	@$(RM) -r $(BIN_PATH)
	@$(RM) -r $(BUILD_PATH)

# checks the executable and symlinks to the output
.PHONY: all
all: $(BINARIES)

# Creation of the executable
$(BIN_PATH)/%: $(OBJECTS) $(MAIN_PATH)/%.$(SRC_EXT)
	@echo "Linking: $@" 
	$(CXX) $(CXXFLAGS) $(MAIN_PATH)/$(notdir $@).$(SRC_EXT) $(OBJECTS) $(INCLUDES) -o $@ ${LIBS}

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@

.PRECIOUS: $(BUILD_PATH)/%.o