#pragma once

#include "Decoder.h"
#include "Memory.h"
#include "Registers.h"
#include "GPU.h"
#include "Visualiser.h"

class Computer {
public:
    Computer();
    
    void tick();

    bool loadProgram(const char* path);
    bool shouldQuit() {return gpu->shouldQuit();}

private:
    int frameCycles_ = 0; // cycles counter PER frame
    static const int FRAME_CYCLES = 5000; // basically clock rate

    Visualiser* vis;
    Decoder* decoder;
    Memory* memory;
    Registers* registers;
    GPU* gpu;
};
