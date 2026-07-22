CPP					:=	g++
CPP_FLAGS_COMMON	:= 	-Wall -Wextra -Wpedantic -Wshadow -std=c++20
CPP_FLAGS_DEBUG		:= 	-g -O0
CPP_FLAGS_RELEASE	:=	-O2 -DNDEBUG

SOURCE_DIR			:=	src
BUILD_DIR			:=	build
RELEASE_DIR			:= $(BUILD_DIR)/release
DEBUG_DIR			:= $(BUILD_DIR)/debug
BIN_DIR				:= bin

BIN_NAME			:= VectorTest.exe

SOURCES				:= $(wildcard $(SOURCE_DIR)/*.cpp)

OBJECTS_DEBUG		:= 	$(patsubst src/%.cpp,$(DEBUG_DIR)/%.o,$(SOURCES))
OBJECTS_RELEASE		:= 	$(patsubst src/%.cpp,$(RELEASE_DIR)/%.o,$(SOURCES))

BINARY_DEBUG		:= 	$(BIN_DIR)/debug/$(BIN_NAME)
BINARY_RELEASE		:=	$(BIN_DIR)/release/$(BIN_NAME)

.PHONY: all release debug clean

all: release

debug: $(BINARY_DEBUG)

release: $(BINARY_RELEASE)

$(BINARY_DEBUG): $(OBJECTS_DEBUG)
	mkdir -p $(BIN_DIR)/debug
	$(CPP) $(OBJECTS_DEBUG) -o $(BINARY_DEBUG)

$(DEBUG_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	mkdir -p $(DEBUG_DIR)
	$(CPP) $(CPP_FLAGS) $(CPP_FLAGS_DEBUG) -c $< -o $@

$(BINARY_RELEASE): $(OBJECTS_RELEASE)
	mkdir -p $(BIN_DIR)/release
	$(CPP) $(OBJECTS_RELEASE) -o $(BINARY_RELEASE)

$(RELEASE_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	mkdir -p $(RELEASE_DIR)
	$(CPP) $(CPP_FLAGS) $(CPP_FLAGS_RELEASE) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)