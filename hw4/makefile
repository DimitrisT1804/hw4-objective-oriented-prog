CXX = g++            # C++ compiler
CXXFLAGS = -Wall -fsanitize=address # Compiler flags
LDFLAGS = -fsanitize=address          # Linker flags
SRC_FILES = $(wildcard *.cpp)   # List of source files
OBJ_FILES = $(SRC_FILES:.cpp=.o)  # List of object files
TARGET = hw4   # Final executable name

# Main rule
all: $(TARGET)

# Compile source files into object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link object files to create the executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(LDFLAGS) $^ -o $@

# Clean compiled files
clean:
	rm -f $(OBJ_FILES) $(TARGET)

.PHONY: all clean