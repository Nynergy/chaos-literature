### VARIABLES ###

# Final target executable
BIN := markovbook

# Compiler
CC := g++

# Source and build output directories
SRC_DIR := src
OBJ_DIR := obj

# List source files
SRC := $(wildcard $(SRC_DIR)/*.cpp)

# From source files, list object files
OBJ := $(SRC:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

# Pass preprocessor flags
CPPFLAGS := -Iinclude # link include directory

# Add compiler flags
CFLAGS := -std=c++14 -Wall

# Add linker flags
LDFLAGS := -L. # link lib directory

# Link against third party libraries
LDLIBS := -lm

### RECIPES ###

# Indicate when a rule does not produce any target output
.PHONY: all clean

all: $(BIN)

# Linking Phase
$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Compiling Phase
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# If build directory does not exist, make it
$(OBJ_DIR):
	mkdir $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f $(BIN)

run: all
	./$(BIN)

# This target will eventually also compile the LaTeX file into a PDF
book: all
	./$(BIN)

debug: all
	gdb ./$(BIN)

# Run executable with valgrind for memory leak analysis
memcheck: all
	valgrind -v ./$(BIN)
