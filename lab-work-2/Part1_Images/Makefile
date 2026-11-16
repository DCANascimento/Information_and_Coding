# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
.DEFAULT_GOAL := all

# Directories
SRC_DIR = src
INC_DIR = include
PROG_DIR = programs
BUILD_DIR = build
BIN_DIR = bin

# Executables
ifeq ($(OS),Windows_NT)
EXE = .exe
else
EXE =
endif

IMG_HIST = $(BIN_DIR)/img_hist$(EXE)
IMG_QUANT = $(BIN_DIR)/img_quant$(EXE)
IMG_CMP = $(BIN_DIR)/img_cmp$(EXE)
TARGETS = $(IMG_HIST) $(IMG_QUANT) $(IMG_CMP)

# Create output directories if they don't exist
ifeq ($(OS),Windows_NT)
directories:
	if not exist "$(BUILD_DIR)" mkdir "$(BUILD_DIR)"
	if not exist "$(BIN_DIR)" mkdir "$(BIN_DIR)"
	if not exist "Histograms" mkdir "Histograms"
else
directories:
	mkdir -p $(BUILD_DIR) $(BIN_DIR) Histograms
endif

# Default target builds all programs; individual targets are available too.
all: $(TARGETS)

img_hist: $(IMG_HIST)
img_quant: $(IMG_QUANT)
img_cmp: $(IMG_CMP)
cmp: $(IMG_CMP)

$(IMG_HIST): $(BUILD_DIR)/read_images.o $(BUILD_DIR)/histograms.o $(BUILD_DIR)/img_hist.o | directories
	$(CXX) $(CXXFLAGS) $^ -o $@

$(IMG_QUANT): $(BUILD_DIR)/read_images.o $(BUILD_DIR)/quantizations.o $(BUILD_DIR)/img_quant.o | directories
	$(CXX) $(CXXFLAGS) $^ -o $@

$(IMG_CMP): $(BUILD_DIR)/read_images.o $(BUILD_DIR)/comparisons.o $(BUILD_DIR)/img_cmp.o | directories
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BUILD_DIR)/read_images.o: $(SRC_DIR)/read_images.cpp $(INC_DIR)/read_images.h $(INC_DIR)/images.h | directories
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/histograms.o: $(SRC_DIR)/histograms.cpp $(INC_DIR)/histograms.h | directories
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/quantizations.o: $(SRC_DIR)/quantizations.cpp $(INC_DIR)/quantizations.h | directories
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/comparisons.o: $(SRC_DIR)/comparisons.cpp $(INC_DIR)/comparisons.h | directories
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/img_hist.o: $(PROG_DIR)/img_hist.cpp $(INC_DIR)/read_images.h $(INC_DIR)/histograms.h $(INC_DIR)/images.h | directories
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/img_quant.o: $(PROG_DIR)/img_quant.cpp $(INC_DIR)/read_images.h $(INC_DIR)/quantizations.h $(INC_DIR)/images.h | directories
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/img_cmp.o: $(PROG_DIR)/img_cmp.cpp $(INC_DIR)/read_images.h $(INC_DIR)/comparisons.h $(INC_DIR)/images.h | directories
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build artifacts
clean:
ifeq ($(OS),Windows_NT)
	if exist "$(BUILD_DIR)" rmdir /S /Q "$(BUILD_DIR)"
	if exist "$(BIN_DIR)" rmdir /S /Q "$(BIN_DIR)"
else
	rm -rf $(BUILD_DIR) $(BIN_DIR)
endif

# Phony targets
.PHONY: all directories clean img_hist img_quant img_cmp cmp