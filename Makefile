# Variables
CC = g++                # C++ compiler (change to clang++ if needed)
CFLAGS = -Wall -O2      # Compiler flags (warnings, optimizations)
INCLUDES = -I./include  # Include path
SRC = src/ZLib/vec.cpp  # Source file (your .cpp file)
OBJ = $(SRC:.cpp=.o)    # Object file
LIB = ./lib/ZLib.so     # Output shared library file
LIB_NAME = ZLib         # Library name for linking
TARGET = $(LIB)         # Target library file

# Rules

# Default target: build the library
all: $(TARGET)

# Build the shared library
$(TARGET): $(OBJ)
	$(CC) -shared -o $@ $^  # Link the object files to create a shared library

# Compile .cpp to .o (object) file
%.o: %.cpp
	$(CC) $(CFLAGS) $(INCLUDES) -fPIC -c $< -o $@

# Clean up compiled files
clean:
	rm -f $(OBJ) $(TARGET)

# Install the library (example: copy to /usr/local/lib)
install: $(TARGET)
	cp $(LIB) /usr/local/lib/
	cp ./include/* /usr/local/include/

# Help command (displays Makefile rules)
help:
	@echo "Makefile commands:"
	@echo "  make          - Build the shared library"
	@echo "  make clean    - Clean up compiled files"
	@echo "  make install  - Install the library and include files"
