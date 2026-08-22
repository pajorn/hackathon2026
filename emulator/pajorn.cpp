#include "Decoder.h"
#include <cstdlib>
#include <cstdio>

int main(void) {
    Registers reg = Registers();
    Memory mem = Memory(&reg);
    uint8_t* a = (uint8_t*)mem.cells_;
    a[0] = 0x01;
    a[1] = 0x34;
    a[2] = 0x34;
    a[3] = 0x12;
    Decoder decoder = Decoder();
    decoder.fdeCycle(&mem, &reg);
    return 0;
}
