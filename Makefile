CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall
SRCS = main.cpp cpu.cpp memory.cpp process.cpp
TARGET = system_monitor

all:
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)