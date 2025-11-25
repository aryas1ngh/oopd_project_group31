# Compiler and Assembler
CXX = g++
AS = as

# Source Files
SRCS = main.cpp Basicio.cpp
ASM_SRC = syscall.s

# Headers (Listed for dependency tracking)
HEADERS = Network.hpp ThreadedTowers.hpp CellTower.hpp FrequencyChannel.hpp MiniSTL.h Basicio.h UserDevice.hpp ThreadedCellTower.hpp

# Base Flags
# -pthread is strictly required for ThreadedCellTower.hpp
# -std=c++17 for modern C++ features
CXXFLAGS_COMMON = -Wall -std=c++17 -pthread

# Target-Specific Flags
# Debug: Includes symbols (-g), disables optimization (-O0), defines DEBUG macro
CXXFLAGS_DEBUG = $(CXXFLAGS_COMMON) -g -O0 -DDEBUG

# Optimized: Max speed (-O3), disables assertions (-DNDEBUG)
CXXFLAGS_OPT = $(CXXFLAGS_COMMON) -O3 -DNDEBUG

# Output Binary Names
TARGET_DEBUG = sim_debug
TARGET_OPT = sim_opt

# Default Target (Builds both)
all: $(TARGET_DEBUG) $(TARGET_OPT)

# Rule for Debug Binary
# 1. Assemble syscall.s
# 2. Compile C++ files with Debug flags and link with syscall object
$(TARGET_DEBUG): $(SRCS) $(ASM_SRC) $(HEADERS)
	@echo "Building Debug Version (sim_debug)..."
	$(AS) $(ASM_SRC) -o syscall.o
	$(CXX) $(CXXFLAGS_DEBUG) $(SRCS) syscall.o -o $(TARGET_DEBUG)

# Rule for Optimized Binary
# 1. Assemble syscall.s
# 2. Compile C++ files with Optimization flags and link with syscall object
$(TARGET_OPT): $(SRCS) $(ASM_SRC) $(HEADERS)
	@echo "Building Optimized Version (sim_opt)..."
	$(AS) $(ASM_SRC) -o syscall.o
	$(CXX) $(CXXFLAGS_OPT) $(SRCS) syscall.o -o $(TARGET_OPT)

# Clean up build files
clean:
	rm -f *.o $(TARGET_DEBUG) $(TARGET_OPT)

.PHONY: all clean