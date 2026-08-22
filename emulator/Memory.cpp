#include "Memory.h"
#include <stdio.h>
#include <cstdlib>
#include <cstring>

Memory::Memory(Registers* reg) {
    //constructor
    //printf("memory contructor\n");
    cells_ = (Word*)malloc(SIZE * sizeof(Word));
    memset(cells_, 0 , SIZE * sizeof(Word));
    activity_ = (uint8_t*)malloc(SIZE);
    memset(activity_, 0, SIZE);


    this->reg = reg;
    // init sp to top of stack space (0xC000)
    // sp points to in use slot, so first push
    // subtracts to 0xBFFFF then writes there
    reg->setSP(STACK_OFFSET + SIZE_REGIONS);
}

Memory::~Memory() {
    free(cells_);
    free(activity_);
}

Word Memory::read(uint16_t address) {
    return cells_[address];
}

void Memory::write(uint16_t address, Word value) {
    cells_[address] = value;
    activity_[address] = 255;
}

void Memory::decayActivity() {
    for (int i = 0; i < SIZE; i++)
        activity_[i] -= activity_[i] >> 3;
}

void Memory::push(uint16_t val) {
    reg->decrementSP();
    write(reg->getSP(), val);
}

uint16_t Memory::pop() {
    uint16_t val = read(reg->getSP());
    reg->incrementSP();
    return val;
}

void Memory::clear() {
    memset(cells_, 0, SIZE * sizeof(Word));
    memset(activity_, 0, SIZE);
}

void Memory::loadProgram(uint16_t* progmem) {
    memcpy(cells_, progmem, SIZE_REGIONS * sizeof(Word));
}

void Memory::exportPixelBuffer(uint16_t* out) {
    memcpy(out, cells_ + PIXEL_OFFSET, SIZE_REGIONS * sizeof(Word));
}
