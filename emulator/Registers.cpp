#include "Registers.h"

Registers::Registers() {
    generalPurpose = new uint16_t[16];
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
}

uint16_t Registers::getSP() {
    return stackPointer;
}

void Registers::incrementSP() {
    stackPointer += 1;
}

void Registers::decrementSP() {
    stackPointer -= 1;
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

