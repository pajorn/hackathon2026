#include <cstdint>

enum class Instruction : uint8_t {
    Move = 0
};

struct InstructionData {
    Instruction instr;
    uint8_t r1;
    uint8_t r2;
    uint16_t address;
};

// fetch decode execute
class Decoder {
public:
    Decoder();

    // instr1 is mem[a], instr2 is mem[a+1]
    InstructionData decodeInstruction(uint16_t instr1, uint16_t instr2);

    // takes the result from decodeInstruction, switches to the corresponding
    // functions via InstructionData.instr
    void execute()

//private:
    // instructions are 4 bytes. First two are instruction related and big
    // endian, 2nd two are whatever g++ chooses (probably little endian).
    // Thus, all numbers (including addresses) will be the same format as
    // the platform.
    uint16_t interpretBigEndian(uint16_t a);


// instructions
};
