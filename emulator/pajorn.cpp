#include "Decoder.h"
#include <cstdlib>
#include <cstdio>

int main(void) {
    uint8_t* a = (uint8_t*)malloc(4 * sizeof(uint8_t));
    a[0] = 0xAA;
    a[1] = 0xBB;
    a[2] = 0xCC;
    a[3] = 0xDD;

    uint16_t instr1 = *((uint16_t*)a);
    a += 2;
    uint16_t instr2 = *((uint16_t*)a);

    printf("%X %X\n", instr1, instr2);

    Decoder* decoder = new Decoder();
    uint32_t out = decoder->interpretBigEndian(instr1);
    printf("%X\n", out);
    decoder->decodeInstruction(instr1, instr2);

    InstructionData data = decoder->decodeInstruction(instr1, instr2);
    printf("instruction: %i, r1: %i, r2: %i, address: %X\n",
	    data.instr, data.r1, data.r2, data.addrImm);
    return 0;
}
