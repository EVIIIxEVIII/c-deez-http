# Compiler
CC := gcc

# Source directory
SRC_DIR := src

# Build directory (where object files and the executable will be placed)
BUILD_DIR := build

# List all the source files with a ".c" extension in the source directory
SRC_FILES := $(wildcard $(SRC_DIR)/*.c)

# Generate corresponding object file names by replacing the ".c" extension with ".o"
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))

# Compiler flags
CFLAGS := -Wall -g

# Executable name
EXECUTABLE := my_program

# Rule to build all object files from source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to link object files and create the executable
$(EXECUTABLE): $(OBJ_FILES)
	$(CC) $(CFLAGS) $^ -o $@

# Default target to build the executable
all: $(EXECUTABLE)

# Clean rule to remove generated object files and the executable
clean:
	rm -f $(BUILD_DIR)/*.o $(EXECUTABLE)

