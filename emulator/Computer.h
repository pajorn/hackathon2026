#pragma once

#include "Decoder.h"
#include "Memory.h"
#include "Registers.h"
#include "GPU.h"

class Computer {
public:
    Computer();

    void tick();

private:
    

    Decoder* decoder;
    Memory* memory;
    Registers* registers;
    GPU* gpu;
};
