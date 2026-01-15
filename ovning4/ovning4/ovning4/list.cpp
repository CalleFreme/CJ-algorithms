#include "list.h"

#include <cstdlib>   // malloc, free
#include <cstdio>    // fprintf
#include <cassert>



// ------------------------------------------------------------
// Hjälpfunktion: skapa en ny nod
// ------------------------------------------------------------
static node* createListNode(Data d) {
    node* newNode = (node*)std::malloc(sizeof(node));
    if (!newNode) return nullptr;
    newNode->d = d;
    newNode->rest = nullptr;
    return newNode;
}

// ------------------------------------------------------------
// Nod-nivå funktioner (C-stil). De ligger inte i List-interfacet.
// ------------------------------------------------------------
static bool nodeIsEmpty(node* l) {
    return l == nullptr;
}

static Data nodeGetFirstElement(node* l) {
    assert(!nodeIsEmpty(l));
    return l->d;
}

static Data nodeGetLastElement(node* l) {
    assert(!nodeIsEmpty(l));
    if (nodeIsEmpty(l->rest)) return l->d;
    return nodeGetLastElement(l->rest);
}

static int nodeAddFirst(node** l, Data d) {
    node* newNode = createListNode(d);
    if (!newNode) return 0;
    newNode->rest = *l;
    *l = newNode;
    return 1;
}

static int nodeAddLast(node** l, Data d) {
    if (nodeIsEmpty(*l)) return nodeAddFirst(l, d);
    return nodeAddLast(&(*l)->rest, d);
}

static void nodeRemoveFirst(node** l) {
    assert(!nodeIsEmpty(*l));
    node* toRemove = *l;
    *l = (*l)->rest;
    std::free(toRemove);
}

static void nodeRemoveLast(node** l) {
    assert(!nodeIsEmpty(*l));

    if (nodeIsEmpty((*l)->rest)) {
        nodeRemoveFirst(l);
        return; // VIKTIGT: stoppa här
    }
    nodeRemoveLast(&(*l)->rest);
}

static int nodeRemoveElement(node** l, Data d) {
    if (nodeIsEmpty(*l)) return 0;

    if (nodeGetFirstElement(*l) == d) {
        nodeRemoveFirst(l);
        return 1;
    }
    return nodeRemoveElement(&(*l)->rest, d);
}

static int nodeIsInList(node* l, Data d) {
    if (nodeIsEmpty(l)) return 0;
    if (nodeGetFirstElement(l) == d) return 1;
    return nodeIsInList(l->rest, d);
}

static int nodeLengthOfList(node* l) {
    if (nodeIsEmpty(l)) return 0;
    return 1 + nodeLengthOfList(l->rest);
}

static void nodeClearList(node** l) {
    while (!nodeIsEmpty(*l)) {
        nodeRemoveFirst(l);
    }
    assert(nodeIsEmpty(*l));
}

/*
  Nybörjarvänlig utskrift: [1, 2, 3]
  - och respekterar den stream som skickas in.
*/
static void nodePrintList(node* l, FILE* stream) {
    std::fputc('[', stream);

    node* cur = l;
    while (cur) {
        std::fprintf(stream, "%d", cur->d);
        cur = cur->rest;
        if (cur) std::fputs(", ", stream);
    }

    std::fputs("]\n", stream);
}

static void nodeForEach(node* l, void (*f)(Data)) {
    node* cur = l;
    while (cur) {
        f(cur->d);
        cur = cur->rest;
    }
}

static void nodeForEachCtx(node* l, void (*f)(Data, void*), void* ctx) {
    node* cur = l;
    while (cur) {
        f(cur->d, ctx);
        cur = cur->rest;
    }
}

// ------------------------------------------------------------
// List-metoder (wrapper runt node-funktionerna)
// ------------------------------------------------------------
List::~List() {
    clearList();
}

bool List::isEmpty() const {
    return start == nullptr;
}

int List::addFirst(Data d) {
    return nodeAddFirst(&start, d);
}

int List::addLast(Data d) {
    return nodeAddLast(&start, d);
}

void List::removeFirst() {
    nodeRemoveFirst(&start);
}

void List::removeLast() {
    nodeRemoveLast(&start);
}

int List::removeElement(Data d) {
    return nodeRemoveElement(&start, d);
}

int List::isInList(Data d) const {
    return nodeIsInList(start, d);
}

int List::lengthOfList() const {
    return nodeLengthOfList(start);
}

void List::clearList() {
    nodeClearList(&start);
}

Data List::getFirstElement() const {
    return nodeGetFirstElement(start);
}

Data List::getLastElement() const {
    return nodeGetLastElement(start);
}

void List::printList(FILE* stream) const {
    nodePrintList(start, stream);
}

void List::forEach(void (*f)(Data)) const {
    nodeForEach(start, f);
}

void List::forEachCtx(void (*f)(Data, void*), void* ctx) const {
    nodeForEachCtx(start, f, ctx);
}