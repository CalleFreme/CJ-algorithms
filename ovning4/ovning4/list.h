#ifndef LIST_H
#define LIST_H

#include <cassert>
#include <cstddef>
#include <cstdio>

// I grunduppgiften lagrar vi int.
// (Om ni senare vill byta typ kan ni ändra här.)
typedef int Data;

struct node {
    Data d;
	struct node* rest;   // pekar på resten av listan (nästa nod). I C++ räcker det egentligen med "node* rest;"
};

/*
  List (int) – enkel enkellänkad lista.
  
  Pedagogisk idé:
  - Vi använder en C++-klass som äger en pekare (start) till första noden.
  - Själva "nod-operationerna" implementeras som hjälpfunktioner i list.cpp.

  Viktigt:
  - Klassen har destruktor -> städar alltid upp minnet (RAII).
  - Kopiering är förbjuden (annars blir det "shallow copy" och dubbel-free).

  Designmål för kursen:
  - Tydligt ADT-gränssnitt
  - Precondition med assert där det behövs
  - RAII: destruktor städar upp minnet
  - Inga templates i grunduppgiften (Data = int)

  Tips:
  - Använd ForEach/ForEachCtx när du behöver iterera utan att exponera noderna.
*/

class List {
private:
    node* start;

public:
    List() : start(nullptr) {}

    // Städar upp allt allokerat minne automatiskt när listan förstörs.
    ~List();

    // Förbjud kopiering (shallow copy av start-pekaren är farligt).
    List(const List&) = delete;
    List& operator=(const List&) = delete;

    // (Valfritt: move kan läggas till senare. Behövs inte i grundkurs.)
    // List(List&&) = default;
    // List& operator=(List&&) = default;

    // ---- Grundoperationer ----
    bool isEmpty() const;

    // Returnerar 1 om lyckades, annars 0 (t.ex. malloc misslyckades)
    int addFirst(Data d);
    int addLast(Data d);

    // Preconditions: listan får inte vara tom
    void removeFirst();
    void removeLast();

    // Tar bort första förekomsten av d. Returnerar 1 om borttagen, annars 0.
    int removeElement(Data d);

    // Returnerar 1 om d finns, annars 0.
    int isInList(Data d) const;

    // Returnerar antal element.
    int lengthOfList() const;

    // Frigör allt minne och gör listan tom.
    void clearList();

    // Skriver ut listan till given stream (stdout om du skickar stdout).
    void printList(FILE* stream) const;

    // Preconditions: listan får inte vara tom
    Data getFirstElement() const;
    Data getLastElement() const;

    // ---- Traversering (iteration) ----

    // Anropar f(x) för varje element x i listan.
    void forEach(void (*f)(Data)) const;

    /*
      forEachCtx: "Ctx" = Context (kontext).

      Callbacks i C/C++ (utan lambdas med capture) kan inte automatiskt "komma åt" lokala variabler utanför funktionen. Därför skickar vi med en extra så kallad "kontext"-pekare (void* ctx) som callbacken kan använda för att nå extra data.
	  Vad är en callback? En funktion som skickas som argument till en annan funktion.

      Exempel:
        struct MyCtx { int sum; };
        
        void add_to_sum(Data x, void* ctx) {
            MyCtx* c = (MyCtx*)ctx;
            c->sum += x;
        }

        MyCtx c{0};
        list.forEachCtx(add_to_sum, &c);
        // c.sum innehåller nu summan av elementen.
    */
    void forEachCtx(void (*f)(Data, void*), void* ctx) const;
};

#endif