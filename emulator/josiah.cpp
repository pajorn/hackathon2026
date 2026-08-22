#include "Memory.h"
#include "GPU.h"
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cmath>


// test display path only
static int testStatic() {
    GPU gpu(4);
    if (!gpu.init())
            return 1;
    uint16_t* buf = new uint16_t[GPU::PIXEL_COUNT];
    GPU::test(buf);
    while (!gpu.shouldQuit()) {
        gpu.pollEvents();
        gpu.present(buf);
    }
    delete[] buf;
    return 0;
}

// test memory path
static int testAnimate() {
    Registers reg;
    Memory mem(&reg);
    GPU gpu(4);
    if (!gpu.init())
        return 1;
    const uint16_t PIXEL_OFFSET = 0xC000;
    int frame = 0;
    while (!gpu.shouldQuit()) {
        gpu.pollEvents();
        for (int y = 0; y < GPU::HEIGHT; y++) {
            for (int x = 0; x < GPU::WIDTH; x++) {
                uint8_t r = (uint8_t)((x * 2 + frame) & 0xFF);
                uint8_t g = (uint8_t)((y * 2 + frame) & 0xFF);
                uint8_t b = (uint8_t)((x * y + frame) & 0xFF);

                bool border = (x == 0 || y == 0 || x == GPU::WIDTH - 1 || y == GPU::HEIGHT - 1);
                uint16_t colour = border ? GPU::rgb555(255, 255, 255)                                          : GPU::rgb555(r, g, b);
                mem.write((uint16_t)(PIXEL_OFFSET + y * GPU::WIDTH + x), colour);
            }
        }
        gpu.drawFrame(&mem);
        frame++;
    }
    return 0;
}

// colour test
static void printColours() {
    printf("black  0x%04X (expect 0x0000)\n", GPU::rgb555(0, 0, 0));
    printf("red    0x%04X (expect 0x7C00)\n", GPU::rgb555(255, 0, 0));
    printf("green  0x%04X (expect 0x03E0)\n", GPU::rgb555(0, 255, 0));
    printf("blue   0x%04X (expect 0x001F)\n", GPU::rgb555(0, 0, 255));
    printf("white  0x%04X (expect 0x7FFF)\n", GPU::rgb555(255, 255, 255));
}

int main(int argc, char** argv) {
    printColours();
    if (argc > 1 && argv[1][0] == 's')
        return testStatic();
    return testAnimate();
}
