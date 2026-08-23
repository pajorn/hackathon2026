#include "Computer.h"
#include <cstdio>
#include <cstring>
Computer::Computer() {
    decoder = new Decoder();
    registers = new Registers();
    memory = new Memory(registers);
    gpu = new GPU();
    gpu->init();
    vis = new Visualiser(2);
    vis->init();
}

void Computer::tick() {
    if (!paused_ || gpu->step) {
        decoder->fdeCycle(memory, registers);
        gpu->step = false;
    }

    if (paused_ || ++frameCycles_ >= FRAME_CYCLES) {
        frameCycles_ = 0;
        gpu->pollEvents();
        if (gpu->pause){
            paused_ = !paused_;
            gpu->pause = false;
        }
        if (gpu->restart) {
            reset();
            gpu->restart = false;
        }
        gpu->drawFrame(memory);
        memory->decayActivity();
        vis->draw(*registers, *memory, paused_); // false is paused_
    }
}

bool Computer::loadProgram(const char* path) {
    FILE* f = fopen(path, "rb");
    memset(program_, 0, sizeof program_);
    // uint16_t buf[Memory::SIZE_REGIONS] = {};
    size_t n = fread(program_, sizeof(uint16_t), Memory::SIZE_REGIONS, f);
    fclose(f);
    printf("loaded %zu words\n", n);
    reset(); // memory->loadProgram in reset 
    return true;
}

void Computer::reset() {
    memory->clear();
    memory->loadProgram(program_);
    registers->setIP(0);
    registers-> setSP(0xC000);
    for (int i = 0; i < 16; i ++) registers->setGP(i, 0);
    registers->setNegative(false);
    registers->setEqual(false);
    frameCycles_ = 0;
    paused_ = false;
}
