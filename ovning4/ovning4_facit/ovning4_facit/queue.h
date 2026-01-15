#ifndef QUEUE_H
#define QUEUE_H

#include "list.h"
#include <cassert>
#include <cstddef>
#include <cstdio>

class Queue {
public:
    using Data = ::Data;

    Queue() = default;

    bool empty() const;
    std::size_t size() const;

    void enqueue(Data value);
    Data peek() const;
    Data dequeue();

    void clear();
    void print(FILE* out = stdout) const;

private:
    List list_;
};

#endif