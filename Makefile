.DELETE_ON_ERROR:

CXX = g++
CFLAGS = -std=c++20 -O3 -Wall -Wextra -Wpedantic -Werror\
-Wduplicated-cond -Woverloaded-virtual -Wnon-virtual-dtor
SRC_DIR = src
SRC = $(wildcard $(SRC_DIR)/*.cpp)
HEADERS = $(wildcard $(SRC_DIR)/*.hpp)
OBJ_DIR = $(SRC_DIR)/obj
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
BIN_DIR = $(SRC_DIR)/bin
EXEC = $(BIN_DIR)/brainfuck

all: $(EXEC)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS)
	@$(CXX) -c -o $@ $< $(CFLAGS)

$(EXEC): $(OBJ)
	@$(CXX) -o $@ $^ $(CFLAGS)

.PHONY: clean cleanall

clean:
	@rm $(OBJ)

cleanall: clean
	@rm $(BIN_DIR)/*
