#include "Decoder.h"
#include <cstdio>

Decoder::Decoder() {
    
}

void Decoder::fdeCycle(Memory* memory, Registers* registers) {
    uint16_t instr1, instr2;
    fetch(memory, registers, &instr1, &instr2);
    InstructionData data = decodeInstruction(instr1, instr2);
    execute(data);
}

void Decoder::fetch(Memory* memory, Registers* registers, uint16_t* instr1, uint16_t* instr2) {
    // read from IP, increment IP
}

InstructionData Decoder::decodeInstruction(uint16_t instr1, uint16_t instr2) {
    uint16_t instructionData  = interpretBigEndian(instr1);
    uint16_t opcode = (instructionData & 0xFC00) >> 10;
    Instruction instr = static_cast<Instruction>((uint8_t)opcode);
    uint16_t address = instr2;
    uint8_t r1 = (instructionData & 0x00F0) >> 4;
    uint8_t r2 = instructionData & 0x000F;
    // printf("instructionData: %X, r1: %i, r2: %i, instruction: %i, address: %X\n",
	// instructionData, r1, r2, instr, address);

    InstructionData data{};
    data.instr = instr;
    data.r1 = r1;
    data.r2 = r2;
    data.address = address;

    return data;
}

void Decoder::execute(InstructionData data) {
    switch (data.instr) {

    }
}

uint16_t Decoder::interpretBigEndian(uint16_t a) {
    uint16_t out;
    out = a << 8 | a >> 8;
    return out;
}
