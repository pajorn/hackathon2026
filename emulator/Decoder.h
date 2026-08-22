#pragma once

#include <cstdint>
#include <cstddef>
#include "Memory.h"
#include "Registers.h"

enum class Operation : uint8_t {
    NOP = 0,
    Move = 1,
    Load = 2,
    Store = 3,
    Jump = 4,
    Push = 5,
    Pop = 6,
    LoadImmediate = 7
};

struct InstructionData {
    Operation instr;
    uint8_t r1;
    uint8_t r2;
    uint16_t addrImm; // address or immediate. depends on instr
};

// fetch decode execute
class Decoder {
public:
    Decoder();

    // does fde. increases IP by 2 cells as full instructions are 2 cells
    void fdeCycle(Memory* memory, Registers* registers);

    void fetch(Memory* memory, Registers* registers, uint16_t* instr1, uint16_t* instr2);

    // instr1 is mem[a], instr2 is mem[a+1]
    InstructionData decodeInstruction(uint16_t instr1, uint16_t instr2);

    // takes the result from decodeInstruction, switches to the corresponding
    // functions via InstructionData.instr
    void execute(InstructionData data, Memory* memory, Registers* registers);

//private:
    // instructions are 4 bytes. First two are instruction related and big
    // endian, 2nd two are whatever g++ chooses (probably little endian).
    // Thus, all numbers (including addresses) will be the same format as
    // the platform.
    uint16_t interpretBigEndian(uint16_t a);


// instructions
};
