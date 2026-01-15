#include "queue.h"

bool Queue::empty() const {
    return list_.isEmpty();
}

std::size_t Queue::size() const {
    return static_cast<std::size_t>(list_.lengthOfList());
}

void Queue::enqueue(Data value) {
    // FIFO: lägg sist
    (void)list_.addLast(value);
}

Queue::Data Queue::peek() const {
    assert(!empty());
    return list_.getFirstElement();
}

Queue::Data Queue::dequeue() {
    assert(!empty());
    Data v = list_.getFirstElement();
    list_.removeFirst();
    return v;
}

void Queue::clear() {
    list_.clearList();
}

void Queue::print(FILE* out) const {
    std::fputs("Queue front -> ", out);
    list_.printList(out);
}