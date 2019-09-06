
TARGET = freak
CXX=clang++
CXXFLAGS += -Wc++11-extensions -std=c++11 -Wall -D__MACOSX_CORE__

TARGET_LIB = libfreak.a
ARFLAGS += -rv

LDFLAGS += -L/usr/lib -L/usr/local/lib -lstdc++ -lfftw3 -lm -pthread
LDFLAGS += -framework CoreFoundation -framework CoreAudio -framework CoreMIDI

INCLUDE = -Iinclude -I/usr/include -I/usr/local/include

OUTPUT_DIR=./bin
BUILD_DIR=./build
OBJ_DIR = $(BUILD_DIR)/.OBJECTS_DIR
TEST_OBJ_DIR = $(BUILD_DIR)/.TEST_OBJECTS_DIR
APP_DIR = $(OUTPUT_DIR)/apps

MKDIR = mkdir -p $(OUTPUTDIR)
TEST = test -d
RM=rm -f

SOURCES += $(wildcard src/*.cpp src/*/*.cpp src/*/*/*.cpp)
OBJS = $(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

OBJ_LIB := $(filter-out $(OBJ_DIR)/src/main.o, $(OBJS))

TARGET_TEST = freak
CXXFLAGS_TEST += $(CXXFLAGS)
LDFLAGSS_TEST += $(LDFLAGS)
INC_TEST += $(INCLUDE) -Itests/catch.hpp
SRC_TEST += $(wildcard tests/*.cpp)
OBJ_TEST += $(filter-out $(OBJ_DIR)/src/main.o, $(OBJS)) $(SRC_TEST:%.cpp=$(TEST_OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<


$(APP_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJS)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*

.PHONY: lib
lib: build_lib $(TARGET_LIB)

build_lib:
	@mkdir -p $(OBJ_DIR)

$(TARGET_LIB) : $(OBJ_LIB)
	ar $(ARFLAGS) $(TARGET_LIB) $(OBJ_LIB)

.PHONY: test
test: build_test $(APP_DIR)/$(TARGET_TEST)

build_test:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(TEST_OBJ_DIR)

$(TEST_OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS_TEST) $(INC_TEST) -o $@ -c $<

$(APP_DIR)/$(TARGET_TEST) : $(OBJ_TEST)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS_TEST) $(INC_TEST) $(LDFLAGSS_TEST) -o $(APP_DIR)/$(TARGET_TEST) $(OBJ_TEST) 