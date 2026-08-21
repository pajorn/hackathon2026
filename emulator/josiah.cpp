#include "Memory.h"
#include <cstdlib>
#include <cstdio>
#include <cassert>

int main(void) {
    Memory mem;
    
    assert(mem.read(0x0000) == 0);
    assert(mem.read(0x1234) == 0);
    assert(mem.read(0xFF00) == 0);

    mem.write(0x6767, 0xABCD);
    assert(mem.read(0x6767) == 0xABCD);
    assert(mem.read(0x6766) == 0);
    assert(mem.read(0x6768) == 0);

    mem.write(0x6767, 0xAAAA);
    assert(mem.read(0x6767) == 0xAAAA);

    mem.clear();
    assert(mem.read(0x6767) == 0);

    printf("pass\n");
    return 0;
}
