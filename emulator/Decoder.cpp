#include "Decoder.h"

Decoder::Decoder() {
    
}

void Decoder::decodeInstruction(uint16_t instr1, uint16_t instr2) {
    // little endian
    uint32_t instr;

}

uint32_t Decoder::interpretBigEndian(uint16_t a, uint16_t b) {
    uint32_t out;
    uint16_t* yes = (uint16_t*)(&out);
    yes[0] = b << 8 | b >> 8;
    yes[1] = a << 8 | a >> 8;
    return out;
}
