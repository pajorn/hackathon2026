#include "Registers.h"
#include <cstdio>

Registers::Registers() {
    generalPurpose = new uint16_t[16];
    instructionPointer = 0;
    stackPointer = 0;
    negativeFlag = false;
    equalFlag = false;
}

void Registers::setGP(uint8_t i, uint16_t val) {
    if (i >= 16)
	return;

    generalPurpose[i] = val;
}

uint16_t Registers::getGP(uint8_t i) {
    if (i >= 16)
	return 0;

    return generalPurpose[i];
}

void Registers::setIP(uint16_t val) {
    instructionPointer = val;
}

void Registers::incrementIP() {
    instructionPointer += 2;
}

uint16_t Registers::getIP() {
    return instructionPointer;
}

void Registers::setSP(uint16_t val) {
    stackPointer = val;
    // printf("stackPointer changed to %04X\n", stackPointer);
}

uint16_t Registers::getSP() {
    return stackPointer;
}

void Registers::incrementSP() {
    setSP(getSP() + 1);
}

void Registers::decrementSP() {
    setSP(getSP() - 1);
}

void Registers::setNegative(bool status) {
    negativeFlag = status;
}

bool Registers::getNegative() {
    return negativeFlag;
}

void Registers::setEqual(bool status) {
    equalFlag = status;
}

bool Registers::getEqual() {
    return equalFlag;
}

void Registers::debugPrint() {
    for (int i = 0; i < 16; i++) {
	printf("r%02i:%04X ", i, generalPurpose[i]);
    }
    printf("IP: %04X, SP: %04X, Negative: %i, Equal: %i\n", instructionPointer,
	    stackPointer, negativeFlag, equalFlag);
}

