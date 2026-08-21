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
    uint32_t out = decoder->interpretBigEndian(instr1, instr2);
    printf("%X\n", out);
    return 0;
}
