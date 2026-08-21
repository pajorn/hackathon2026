#pragma once

class Computer {
public:
    Computer();

private:
    Decoder* decoder;
    Memory* memory;
    Stack* stack;
    Registers* registers;
    Renderer* renderer;
};
