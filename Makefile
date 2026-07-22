######################################################################################################

###############
## TOOLCHAIN ##
###############
CPP						:= g++

###########################
## PREPROCESSOR SETTINGS ##
###########################
INCLUDE_DIRS			:= include
INCLUDE					:= $(addprefix -I, $(INCLUDE_DIRS))
DEFINES_COMMON			:=
DEFINES_DEBUG			:=
DEFINES_RELEASE			:= NDEBUG

DEFINES_DEBUG			:= $(addprefix -D, $(DEFINES_COMMON)) \
						   $(addprefix -D, $(DEFINES_DEBUG))
DEFINES_RELEASE			:= $(addprefix -D, $(DEFINES_COMMON)) \
						   $(addprefix -D, $(DEFINES_RELEASE))

#######################
## COMPILER SETTINGS ##
#######################
WARNING_FLAGS			:= 	-Wall -Wextra -Wpedantic -Wshadow
CPP_STD					:=	-std=c++20
CPP_FLAGS_COMMON		:= $(WARNING_FLAGS) $(CPP_STD) $(INCLUDE)
CPP_FLAGS_DEBUG			:= -g -O0
CPP_FLAGS_RELEASE		:= -O2

###################
## LINKER CONFIG ##
###################
SYSTEM_LIBS				:=
PROJECT_LIBS_DIRS		:=
PROJECT_LIBS			:=

PROJECT_LIB_DIR_FLAGS 	:= $(addprefix -L, $(PROJECT_LIBS))
PROJECT_LIB_FLAGS		:= $(addprefix -L, $(PROJECT_LIBS))
SYSTEM_LIB_FLAGS		:= $(addprefix -l, $(SYSTEM_LIBS))

LINKER_FLAGS			:= $(PROJECT_LIB_DIR_FLAGS) $(PROJECT_LIB_FLAGS) $(SYSTEM_LIB_FLAGS)

######################
## DIRECTORY CONFIG ##
######################
SOURCE_DIR				:= src
BUILD_DIR				:= build
RELEASE_DIR				:= $(BUILD_DIR)/release
DEBUG_DIR				:= $(BUILD_DIR)/debug
BIN_DIR					:= bin

###################
## OUTPUT CONFIG ##
###################
BIN_NAME				:= VectorTest.exe

#####################
## ARTIFACT CONFIG ##
#####################
SOURCES					:= $(wildcard $(SOURCE_DIR)/*.cpp)

OBJECTS_DEBUG			:= $(patsubst $(SOURCE_DIR)/%.cpp,$(DEBUG_DIR)/%.o,$(SOURCES))
OBJECTS_RELEASE			:= $(patsubst $(SOURCE_DIR)/%.cpp,$(RELEASE_DIR)/%.o,$(SOURCES))

BINARY_DEBUG			:= $(BIN_DIR)/debug/$(BIN_NAME)
BINARY_RELEASE			:= $(BIN_DIR)/release/$(BIN_NAME)

######################################################################################################

.PHONY: all release debug clean

release: $(BINARY_RELEASE)

debug: $(BINARY_DEBUG)

all: release debug

## DEBUG BUILD RECIPES ##============================================================================

##################
## *.cpp -> *.o ##
##################
$(DEBUG_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	mkdir -p $(DEBUG_DIR)
	$(CPP) $(CPP_FLAGS_COMMON) $(CPP_FLAGS_DEBUG) $(DEFINES_DEBUG) -c $< -o $@

#######################
## *.o -> Executable ##
#######################
$(BINARY_DEBUG): $(OBJECTS_DEBUG)
	mkdir -p $(BIN_DIR)/debug
	$(CPP) $(OBJECTS_DEBUG) $(LINKER_FLAGS) -o $(BINARY_DEBUG)

## RELEASE BUILD RECIPES ## =========================================================================

##################
## *.cpp -> *.o ##
##################
$(RELEASE_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	mkdir -p $(RELEASE_DIR)
	$(CPP) $(CPP_FLAGS_COMMON) $(CPP_FLAGS_RELEASE) $(DEFINES_RELEASE) -c $< -o $@

#######################
## *.o -> Executable ##
#######################
$(BINARY_RELEASE): $(OBJECTS_RELEASE)
	mkdir -p $(BIN_DIR)/release
	$(CPP) $(OBJECTS_RELEASE) $(LINKER_FLAGS) -o $(BINARY_RELEASE)

clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)