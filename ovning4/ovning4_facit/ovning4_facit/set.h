#ifndef SET_H
#define SET_H

#include "list.h"
#include <cassert>
#include <cstddef>
#include <cstdio>

class Set {
public:
    using Data = ::Data;

    Set() = default;

    bool empty() const;
    std::size_t size() const;

    bool contains(Data x) const;
    bool add(Data x);
    bool remove(Data x);

    void clear();
    void print(FILE* out = stdout) const;

    static Set set_union(const Set& a, const Set& b);
    static Set set_intersection(const Set& a, const Set& b);
    static Set set_difference(const Set& a, const Set& b);

private:
    List list_;
};

#endif