CXX = g++
CXXFLAGS = -Wall

all: emulator

emulator: main.o Memory.o
	$(CXX) $(CXXFLAGS) -o emulator main.o Memory.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

memory.o: Memory.cpp Memory.h
	$(CXX) $(CXXFLAGS) -c Memory.cpp Memory.h

.PHONY: clean

clean:
	rm -f *.o emulator
