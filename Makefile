SRC_DIR = src
BUILD_DIR = build
EXE = mango

SRC = main.cpp token.cpp scanner.cpp mango.cpp ast_printer.cpp parser.cpp
OBJ = $(SRC:%.cpp=$(BUILD_DIR)/%.o)

CXXFLAGS += -std=c++23 -Wall -Wextra -Werror -pedantic
# CXX = g++

all: debug

release: setup
release: CXXFLAGS += -O3 -DNDEBUG
release: $(BUILD_DIR)/$(EXE)

debug: setup
debug: CXXFLAGS += -g
debug: $(BUILD_DIR)/$(EXE)

debug-memory: setup
debug-memory: CXXFLAGS += -g -fsanitize=address,undefined
debug-memory: $(BUILD_DIR)/$(EXE)

.PHONY: all debug release clean setup

setup:
	mkdir -p build/

clean:
	rm -rf build

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

$(BUILD_DIR)/$(EXE): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@
