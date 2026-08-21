#include "Memory.h"
#include <stdio.h>
#include <cstdlib>
#include <cstring>

Memory::Memory() {
    //constructor
    //printf("memory contructor\n");
    cells_ = (Word*)malloc(SIZE * sizeof(Word));
    memset(cells_, 0 , SIZE * sizeof(Word));
}

Memory::~Memory() {
    free(cells_);
}

Word Memory::read(uint16_t address) const {
    return cells_[address];
}

void Memory::write(uint16_t address, Word value) {
    cells_[address] = value;
}

void Memory::clear() {
    memset(cells_, 0, SIZE * sizeof(Word));
}
