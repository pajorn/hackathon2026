class Memory {
public:
    Memory();
    ~Memory();

    Word read(uint16_t address) const;
    void write(uint16_t address, Word value);
    void clear();
private:
    static const int SIZE = 65536; // 2^16 
    Word* cells_;

    // NO COPYING
    Memory(const Memory&) = delete;
    Memory& operator=(const Memory&) = delete;
};
