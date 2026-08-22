#include "Computer.h"

Computer::Computer() {
    decoder = new Decoder();
    registers = new Registers();
    memory = new Memory(registers);
    gpu = new GPU();
}

void Computer::tick() {
    decoder->fdeCycle(memory, registers);
}
