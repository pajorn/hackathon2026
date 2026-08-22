#include "Computer.h"
#include <cstdio>

Computer::Computer() {
    decoder = new Decoder();
    registers = new Registers();
    memory = new Memory(registers);
    gpu = new GPU();
<<<<<<< HEAD
    gpu->init();
=======
    vis = new Visualiser(2);
    vis->init();
>>>>>>> 9e321fc (idgaf)
}

void Computer::tick() {
    decoder->fdeCycle(memory, registers);

    if (++frameCycles_ >= FRAME_CYCLES) {
        frameCycles_ = 0;
        gpu->pollEvents();
        gpu->drawFrame(memory);
        memory->decayActivity();
        vis->drawFrame(*registers, *memory, false);
    }
}

bool Computer::loadProgram(const char* path) {
    FILE* f = fopen(path, "rb");
    uint16_t buf[Memory::SIZE_REGIONS] = {};
    size_t n = fread(buf, sizeof(uint16_t), Memory::SIZE_REGIONS, f);
    fclose(f);
    memory->loadProgram(buf);
    printf("loaded %zu words\n", n);
    return true;
}
