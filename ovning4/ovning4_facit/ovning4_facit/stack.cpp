#include "stack.h"

bool Stack::empty() const {
    return list_.isEmpty();
}

std::size_t Stack::size() const {
    return static_cast<std::size_t>(list_.lengthOfList());
}

void Stack::push(Data value) {
    // LIFO: toppen = första elementet
    (void)list_.addFirst(value);
    // addFirst returnerar 0/1; i kursen kan man ignorera OOM,
    // eller välja att assert:a om ni vill.
}

Stack::Data Stack::peek() const {
    assert(!empty());
    return list_.getFirstElement();
}

Stack::Data Stack::pop() {
    assert(!empty());
    Data v = list_.getFirstElement();
    list_.removeFirst();
    return v;
}

void Stack::clear() {
    list_.clearList();
}

void Stack::print(FILE* out) const {
    std::fputs("Stack top -> ", out);
    list_.printList(out);
}