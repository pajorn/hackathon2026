#pragma once

#include <cstdint>
#include <cstddef>
#include "Registers.h"

using Word = uint16_t;

class Memory {
public:
    Memory(Registers* reg);
    ~Memory();

    Word read(uint16_t address);
    void write(uint16_t address, Word value);
    void clear();

    void push(uint16_t val);
    uint16_t pop();

    // place into PROG_OFFSET. progmem must be size 0x4000
    void loadProgram(uint16_t* progmem);

    // copies the pixel buffer to out. out must have size 0x4000
    void exportPixelBuffer(uint16_t* out);
private:
    Registers* reg;

    static const size_t SIZE = 0xFFFF; // 2^16 

    // each region has size 0x4000
    static const size_t SIZE_REGIONS = 0x4000;
    static const size_t PROG_OFFSET = 0x0000;
    static const size_t HEAP_OFFSET = 0x4000;
    static const size_t STACK_OFFSET = 0x8000;
    static const size_t PIXEL_OFFSET = 0xC000;
    
    Word* cells_;

    // NO COPYING
    Memory(const Memory&) = delete;
    Memory& operator=(const Memory&) = delete;
};
