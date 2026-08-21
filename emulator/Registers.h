#include <cstdint>

class Registers {
public:
    Registers();

    void setGP(uint8_t i, uint16_t val);
    uint16_t getGP(uint8_t i);

    void setIP(uint16_t val);
    uint16_t getIP();

    void setSP(uint16_t val);
    uint16_t getSP();

private:
    uint16_t* generalPurpose;
    uint16_t instructionPointer;
    uint16_t stackPointer;
};
