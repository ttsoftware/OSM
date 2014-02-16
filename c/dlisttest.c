#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dlist.h"

/*
 * Prints the contents of a dlist
 */
void printdlist(dlist *list) {
	node *current_item = list->head;
	node *prev = NULL;
	while (current_item != NULL) {
		printf("%d\n", *((int*)current_item->thing));

		node* temp = current_item;
		current_item = (node*) ((uintptr_t)(current_item->ptr) ^ (uintptr_t)prev);
		prev = temp;
	}
}

/*
 * An example of an input function to the search method.
 */
bool findInt(item *el) {
	if (*((int*)el) == 2) {
		return 1;
	}
	return 0;
}

int main(void) {

	int a = 1;
	int b = 2;
	int c = 3;
	int d = 4;

	struct dlist_ *list = (struct dlist_ *) malloc (sizeof (struct dlist_));

	// insert
	insert(list, &a, 0);
	insert(list, &b, 0);
	insert(list, &c, 0);
	insert(list, &d, 0);

	// search
	printf("%d\n", *((int*)search(list, &findInt))); // 2

	// reverse
	reverse(list);
	// print reversed list
	printdlist(list); // 1, 2, 3, 4

	// extract head
	printf("%d\n", *((int*)extract(list, 0))); // 1
	
	// extract tail
	printf("%d\n", *((int*)extract(list, 1))); // 4

	// print the list to ensure elements 1 and 4 has been extracted.
	printdlist(list); // 2, 3

	printf("%s\n", "Above should be printed: 2 1 2 3 4 1 4 2 3");
	return 0;
}