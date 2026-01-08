
#ifndef LIST_H
#define LIST_H

#include <stdio.h>

typedef int Data; //ifall vi någonsin vi vill ändra typen av sparat data

struct node {
	Data d;
	struct node* rest; //notera att detta är en lista
};

typedef struct node* List; //nodepointers är listor



//INTERFACE

//skapar och returnerar en ny lista
List createEmptyList(void);

//undersöker om en lista är tom
int isEmpty(List l);

//lägger till 'd' först i listan
//returnerar 1 ifall lyckades, annars 0
// O(1)
int addFirst(List* l, Data d);

//lägger till 'd' sist i listan
//returnerar 1 ifall lyckades, annars 0
// O(n) med nuvarande design
int addLast(List* l, Data d);

//tar bort första noden från listan
void removeFirst(List* l);

//tar bort sista noden från listan
// O(n), måste gå igenom hela listan för att hitta näst sista noden med nuvarande design
void removeLast(List* l);

//tar bort första förekomsten av 'd' från listan
//returnerar 1 ifall elementet fanns, annars 0
int removeElement(List* l, Data d);

//undersök om datat 'd' finns i listan
//returnerar 1 ifall det finns, annars 0
// O(n)
int isInList(List l, Data d);

//returnerar antal element i listan
int lengthOfList(List l);

//tömmer listan och frigör allt minne
void clearList(List* l);

//skriver ut alla element i listan till den angivna strömmen
void printList(List l, FILE* stream);

//returnerar värdet på första datat i listan
Data getFirstElement(List l);

//returnerar värdet på sista datat i listan
Data getLastElement(List l);

#endif
