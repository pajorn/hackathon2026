#include "Memory.h"
#include "Computer.h"
//includes here

int main(int argc, char** argv) {
    Computer c;
    if (!c.loadProgram(argv[1]))
        return 1
    while (!c.shouldQuit())
        c.tick();
    return 0;
}
