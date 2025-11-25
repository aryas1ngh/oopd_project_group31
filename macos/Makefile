# macOS-specific Makefile
# Run this from inside the 'macos' directory.
# Example: cd macos && make

# Compiler and Assembler
CXX = g++
AS = as

# Architecture Flags
# CRITICAL FOR M1/M2/M3: 
# This forces the build to use the x86_64 instruction set.
# This allows the 'syscall.s' (which is written for Intel) to work
# on your machine using macOS's built-in Rosetta 2 translation.
ARCH_FLAGS = -arch x86_64

# Directory Paths
SRC_DIR = ..

# Source Files (Relative to this makefile)
SRCS = $(SRC_DIR)/main.cpp $(SRC_DIR)/Basicio.cpp
ASM_SRC = syscall.s

# Headers (For dependency tracking)
HEADERS = $(SRC_DIR)/Network.hpp \
          $(SRC_DIR)/ThreadedTowers.hpp \
          $(SRC_DIR)/CellTower.hpp \
          $(SRC_DIR)/FrequencyChannel.hpp \
          $(SRC_DIR)/MiniSTL.h \
          $(SRC_DIR)/Basicio.h \
          $(SRC_DIR)/UserDevice.hpp \
          $(SRC_DIR)/ThreadedCellTower.hpp \
          $(SRC_DIR)/CellularCore.hpp

# Compiler Flags
# -I$(SRC_DIR) is needed to find the header files in the parent folder.
CXXFLAGS_COMMON = -Wall -std=c++17 -I$(SRC_DIR) $(ARCH_FLAGS)

# Debug Flags
CXXFLAGS_DEBUG = $(CXXFLAGS_COMMON) -g -O0 -DDEBUG

# Optimization Flags
CXXFLAGS_OPT = $(CXXFLAGS_COMMON) -O3 -DNDEBUG

# Output Binary Names
TARGET_DEBUG = sim_debug
TARGET_OPT = sim_opt

# Default Target
all: $(TARGET_DEBUG) $(TARGET_OPT)

# Build Debug Version
$(TARGET_DEBUG): $(SRCS) $(ASM_SRC) $(HEADERS)
	@echo "Building macOS Debug Version (sim_debug)..."
	$(AS) $(ARCH_FLAGS) $(ASM_SRC) -o syscall.o
	$(CXX) $(CXXFLAGS_DEBUG) $(SRCS) syscall.o -o $(TARGET_DEBUG)

# Build Optimized Version
$(TARGET_OPT): $(SRCS) $(ASM_SRC) $(HEADERS)
	@echo "Building macOS Optimized Version (sim_opt)..."
	$(AS) $(ARCH_FLAGS) $(ASM_SRC) -o syscall.o
	$(CXX) $(CXXFLAGS_OPT) $(SRCS) syscall.o -o $(TARGET_OPT)

# Clean
clean:
	rm -f *.o $(TARGET_DEBUG) $(TARGET_OPT)

.PHONY: all clean