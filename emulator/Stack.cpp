#include "Stack.h"
#include <cassert>

Stack::Stack() : items_{}, sp_(0) {
}

void Stack::push(Word value) {
    assert(!full());
    items_[sp_] = value;
    sp_++;
}

Word Stack::pop() {
    assert(!empty());
    sp_--;
    return items_[sp_];
}

Word Stack::peek() {
    assert(!empty());
    return items_[sp_ - 1];
}

bool Stack::empty() {
    return sp_ == 0;
}

bool Stack::full() {
    return sp_ == SIZE;
}

void Stack::clear() {
    sp_ = 0;
}
