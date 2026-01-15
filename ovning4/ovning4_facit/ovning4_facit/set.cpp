#include "set.h"

// ---- Grundmetoder ----

bool Set::empty() const {
    return list_.isEmpty();
}

std::size_t Set::size() const {
    return static_cast<std::size_t>(list_.lengthOfList());
}

bool Set::contains(Data x) const {
    return list_.isInList(x) != 0;
}

bool Set::add(Data x) {
    if (contains(x)) return false;
    (void)list_.addLast(x);
    return true;
}

bool Set::remove(Data x) {
    return list_.removeElement(x) != 0;
}

void Set::clear() {
    list_.clearList();
}

void Set::print(FILE* out) const {
    std::fputs("Set ", out);
    list_.printList(out);
}

// ---- Set-operationer via forEachCtx ----

namespace {
    struct OutCtx { Set* out; };
    void add_to_out(Data x, void* ctx) {
        auto* c = static_cast<OutCtx*>(ctx);
        c->out->add(x);
    }

    struct OtherOutCtx { const Set* other; Set* out; };
    void add_if_in_other(Data x, void* ctx) {
        auto* c = static_cast<OtherOutCtx*>(ctx);
        if (c->other->contains(x)) c->out->add(x);
    }
    void add_if_not_in_other(Data x, void* ctx) {
        auto* c = static_cast<OtherOutCtx*>(ctx);
        if (!c->other->contains(x)) c->out->add(x);
    }
}

Set Set::set_union(const Set& a, const Set& b) {
    Set r;
    OutCtx ctx{ &r };
    a.list_.forEachCtx(add_to_out, &ctx);
    b.list_.forEachCtx(add_to_out, &ctx);
    return r;
}

Set Set::set_intersection(const Set& a, const Set& b) {
    Set r;
    OtherOutCtx ctx{ &b, &r };
    a.list_.forEachCtx(add_if_in_other, &ctx);
    return r;
}

Set Set::set_difference(const Set& a, const Set& b) {
    Set r;
    OtherOutCtx ctx{ &b, &r };
    a.list_.forEachCtx(add_if_not_in_other, &ctx);
    return r;
}