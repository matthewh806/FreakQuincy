TARGET=bodeplotter
CXX=clang++
CXXFLAGS+=-Wc++11-extensions -std=c++11 -Wall -D__MACOSX_CORE__

INCLUDE=-Iinclude -Iusr/include -I/usr/local/include -I$(LIB_DIR)/include

LIB_DIR=../../lib

LDFLAGS += -L/usr/lib -L/usr/local/lib -lstdc++ -lm -pthread $(LIB_DIR)/libfreak.a -lboost_iostreams -lboost_system -lboost_filesystem

BUILD_DIR=./build
APP_DIR=$(BUILD_DIR)/apps
OBJ_DIR=$(BUILD_DIR)/OBJECTS_DIR

SOURCES+=$(wildcard src/*.cpp)
OBJS:=$(SOURCES:%.cpp=$(OBJ_DIR)/%.o)

all: build $(APP_DIR)/$(TARGET)

.PHONY: all build clean debug release

build:
	@mkdir -p $(APP_DIR)
	@mkdir -p $(OBJ_DIR)

debug: CXXFLAGS += -DDEBUG -g
debug: all

release: CXXFLAGS += -O2
release: all

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<


$(APP_DIR)/$(TARGET): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(LDFLAGS) -o $(APP_DIR)/$(TARGET) $(OBJS)

clean:
	-@rm -rvf $(OBJ_DIR)/*
	-@rm -rvf $(APP_DIR)/*