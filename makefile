# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

# Executable
TARGET = payroll_app

# Finds all .cpp files
SRCS = $(wildcard *.cpp)

# translates .cpp into .o files
OBJS = $(SRCS:.cpp=.o)

# default target
all: $(TARGET)

# Combines all object files into the final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Converts ANY .cpp file into a .o file
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean