#include "Memory.h"
#include "GPU.h"
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>

const uint16_t PIXEL_OFFSET = 0xC000;

static int testTest() {
    Registers reg;
    Memory mem(&reg);
    GPU gpu(4);
    if (!gpu.init())
        return 1;

    const uint16_t BOB = GPU::rgb555(0, 255, 0);
    const uint16_t BG = GPU::rgb555(0, 0, 0);
    int x = 0, y = 0;
    while (!gpu.shouldQuit()) {
        gpu.pollEvents();
        uint16_t addr = (uint16_t)(PIXEL_OFFSET + y * GPU::WIDTH + x);
        mem.write(addr, BOB);
        gpu.drawFrame(&mem);
        mem.write(addr, BG);

        if (++x >= GPU::WIDTH) {
            x = 0;
            if (++y >= GPU::HEIGHT)
                y = 0;
        }
    }
    return 0;
}

int main(void) {
    return testTest();
}
