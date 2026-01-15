#ifndef STACK_H
#define STACK_H

#include "list.h"
#include <cassert>
#include <cstddef>
#include <cstdio>

class Stack {
public:
    using Data = ::Data;

    Stack() = default;

    bool empty() const;
    std::size_t size() const;

    void push(Data value);
    Data peek() const;
    Data pop();

    void clear();
    void print(FILE* out = stdout) const;

private:
    List list_;
};

#endif