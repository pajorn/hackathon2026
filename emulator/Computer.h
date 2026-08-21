#pragma once

class Computer {
public:
    Computer();

private:
    Decoder* decoder;
    Memory* memory;
    Registers* registers;
    GPU* gpu;
};
