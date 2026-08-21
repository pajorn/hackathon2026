#pragma once
#include <cstdint>

using Word = uint16_t;

class Stack {
public:
    Stack();

    void push(Word value);
    Word pop();
    Word peek() const;

    bool empty() const;
    bool full() const;
    void clear;

private:
    static const int SIZE = 256;
    Word items_[SIZE];
    unit16_t sp_;
};
