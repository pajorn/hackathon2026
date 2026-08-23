#include "Memory.h"
#include "Computer.h"
//includes here

int main(int argc, char** argv) {
    if (argc != 2) {
        printf("usage: emulator program.bin\n");
        return 1;
    }
    Computer* c = new Computer();
    if (!c->loadProgram(argv[1]))
        return 1;
    while (!c->shouldQuit())
        c->tick();
    return 0;
}
