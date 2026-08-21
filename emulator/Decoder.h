#include <cstdint>

class Decoder {
public:
    Decoder();

    // instr1 is mem[a], instr2 is mem[a+1]
    void decodeInstruction(uint16_t instr1, uint16_t instr2);

//private:
    // mem: 0xAABBCCDD, a: 0xBBAA, b: 0xDDCC
    uint32_t interpretBigEndian(uint16_t a, uint16_t b);
};
