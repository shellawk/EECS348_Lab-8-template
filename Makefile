# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic

# Targets
TARGET = matrix_operations
SRCS = main.cpp matrix.cpp
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Build main executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile .cpp files to .o files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build and run tests
test: build_tests
	cd build && ctest --output-on-failure

# Configure and build tests
build_tests:
	mkdir -p build && cd build && cmake .. && make

# Clean up
clean:
	rm -f $(TARGET) $(OBJS)
	rm -rf build

# Phony targets (don't represent actual files)
.PHONY: all clean test build_tests