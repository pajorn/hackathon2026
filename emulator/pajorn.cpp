#include "Decoder.h"
#include <cstdlib>
#include <cstdio>

int main(int argc, char** argv) {
    if (argc != 2) {
	printf("incorrect no. of args\n");
	return 1;
    }
    printf("%s\n", argv[1]);
    Registers reg = Registers();
    Memory mem = Memory(&reg);

    FILE* program = fopen(argv[1], "rb");
    if (program == NULL) {
	printf("couldn't open\n");
	return 1;
    }
    fread(mem.cells_, 1, 0x4000 * 2, program);

    uint8_t* a = (uint8_t*)mem.cells_;
    // a[0] = 0x01;
    // a[1] = 0x34;
    // a[2] = 0x34;
    // a[3] = 0x12;
    for (int i = 0; i < 2 * 0x0A; i++)
	printf("%02X ", a[i]);
    Decoder decoder = Decoder();
    decoder.fdeCycle(&mem, &reg);
    return 0;
}
