#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

/*
	createListNode() finns för att göra koden lättare
	att skriva. det är en så kallad hjälpfunktion.

	den är _inte_ med i interfacet, och är därmed static.

	vad den ska göra:
	allokera minne för en ny nod
	undersök om allokering lyckas
		returnera NULL ifall mislyckas
	initiera noden
	returnera noden */

static struct node* createListNode(Data d) {
	// Denna funktion ska göra EN sak bra: allokera minne för en ny nod, check for NULL, och initiera 'd' och 'rest'.
	return NULL; //endast här för kompilering
}


//----

List createEmptyList(void) {
	return NULL; //är korrekt, ändra inte
}

int isEmpty(List l) {
	return 0; //endast här för kompilering
}

int addFirst(List* l, Data d) {
	// Vi skickar List* så att funktionen kan uppdatera listans startadress/pekare till startnod.
	return 0; //endast här för kompilering
}

int addLast(List* l, Data d) {
	// Utan en tail pointer måste vi iterera till slutet av listan för att lägga till en nod sist.
	// Du kan låta din ADT lagra pekare till både första (head) och sista noden (tail) för att undvika detta.
	return 0; //endast här för kompilering
}

void removeFirst(List* l) {
	//precondition: listan är inte tom (testa med assert)
	// Du vill använda dig av assert här för att kontrollera precondition.
	// Exempel: assert(!isEmpty(*l));
}

void removeLast(List* l) {
	// Tänk på att du måste hantera fallet där listan bara har ett element.
	//precondition: listan är inte tom (testa med assert)
}

int removeElement(List* l, Data d) {
	// Se till att ta bort första noden korrekt. Behöver ha koll på föregående nod när du itererar.
	return 0; //endast här för kompilering
}

int isInList(List l, Data d) {
	return 0; //endast här för kompilering
}

int lengthOfList(List l) {
	return 0; //endast här för kompilering
}

void clearList(List* l) {
	// Enklast och säkrast att köra removeFirst i en loop tills listan är tom.
	//postcondition: listan är tom (testa med assert)
}

void printList(List l, FILE* stream) {
	// Tom lista ska skriva ut: []
	// Icke-tom lista ska skriva ut: [data1, data2, data3]
}

Data getFirstElement(List l) {
	//precondition: listan är inte tom (testa med assert)
	return 0; //endast här för kompilering
}

Data getLastElement(List l) {
	//precondition: listan är inte tom (testa med assert)
	return 0; //endast här för kompilering
}
