#include "Decoder.h"
#include <cstdio>

Decoder::Decoder() {
    
}

void Decoder::fdeCycle(Memory* memory, Registers* registers) {
    uint16_t instr1, instr2;
    fetch(memory, registers, &instr1, &instr2);
    InstructionData data = decodeInstruction(instr1, instr2);
    execute(data, memory, registers);
}

void Decoder::fetch(Memory* memory, Registers* registers, uint16_t* instr1, uint16_t* instr2) {
    // read from IP, increment IP
    instr1 = mem->read(reg->getIP());
    instr1 = mem->read(reg->getIP() + 1);
    reg->incrementIP();
}

InstructionData Decoder::decodeInstruction(uint16_t instr1, uint16_t instr2) {
    uint16_t instructionData  = interpretBigEndian(instr1);
    uint16_t opcode = (instructionData & 0x3F00) >> 8;
    Operation instr = static_cast<Operation>((uint8_t)opcode);
    uint16_t address = instr2;
    uint8_t r1 = (instructionData & 0x00F0) >> 4;
    uint8_t r2 = instructionData & 0x000F;
    // printf("instructionData: %X, r1: %i, r2: %i, instruction: %i, address: %X\n",
	// instructionData, r1, r2, instr, address);

    InstructionData data{};
    data.instr = instr;
    data.r1 = r1;
    data.r2 = r2;
    data.addrImm = address;

    return data;
}

void Decoder::execute(InstructionData data, Memory* mem, Registers* reg) {
    switch (data.instr) {
	case Operation::Move:
	    reg->setGP(data.r1, reg->getGP(data.r2));
	    break;
	case Operation::Load:
	    reg->setGP(data.r1, mem->read(reg->getGP(data.r2)));
	    break;
	case Operation::Store:
	    mem->write(reg->getGP(data.r2), reg->getGP(data.r1));
	    break;
	case Operation::Jump:
	    reg->setIP(data.addrImm);
	    break;
	case Operation::Push:
	    mem->push(reg->getGP(data.r1));
	    break;
	case Operation::Pop:
	    reg->setGP(data.r1, mem->pop());
	    break;
	case Operation::LoadImmediate:
	    reg->setGP(data.r1, data.addrImm);
	    break;
    }
}

uint16_t Decoder::interpretBigEndian(uint16_t a) {
    uint16_t out;
    out = a << 8 | a >> 8;
    return out;
}
