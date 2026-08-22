#include "Decoder.h"
#include "Computer.h"
#include <cstdlib>
#include <cstdio>

int main(int argc, char** argv) {
    if (argc != 2) {
	printf("incorrect no. of args\n");
	return 1;
    }

    Computer computer = Computer();
    computer.loadProgram(argv[1]);
    uint8_t* a = (uint8_t*)computer.memory->cells_;
    for (int i = 0; i < 2 * 0x0A; i++)
	printf("%02X ", a[i]);
    printf("\n");

    for (int i = 0; i < 15; i++) {
	computer.tick();
    }

    return 0;
}
