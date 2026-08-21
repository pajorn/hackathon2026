CXX = g++
CXXFLAGS = -Wall

all: emulator

emulator: main.o Decoder.o Memory.o Registers.o GPU.o
	$(CXX) $(CXXFLAGS) -o emulator main.o Decoder.o Memory.o Registers.o GPU.o

pajorn: pajorn.cpp Decoder.o Memory.o Registers.o GPU.o
	$(CXX) $(CXXFLAGS) -c pajorn.cpp
	$(CXX) $(CXXFLAGS) -o pajorn pajorn.o Decoder.o Memory.o Registers.o GPU.o

josiah: josiah.cpp Decoder.o Memory.o Registers.o GPU.o
	$(CXX) $(CXXFLAGS) -c josiah.cpp
	$(CXX) $(CXXFLAGS) -o josiah josiah.o Decoder.o Memory.o Registers.o GPU.o

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Decoder.o: Decoder.cpp Decoder.h
	$(CXX) $(CXXFLAGS) -c Decoder.cpp Decoder.h

Memory.o: Memory.cpp Memory.h
	$(CXX) $(CXXFLAGS) -c Memory.cpp Memory.h

Registers.o: Registers.cpp Registers.h
	$(CXX) $(CXXFLAGS) -c Registers.cpp Registers.h

GPU.o: GPU.cpp GPU.h
	$(CXX) $(CXXFLAGS) -c GPU.cpp GPU.h

.PHONY: clean

clean:
	rm -f *.o emulator
