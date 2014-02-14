#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "dlist.h"

int main(void)
{

	int a = 1;
	int b = 2;
	int c = 3;
	int d = 2;

	struct dlist_ *list = (struct dlist_ *) malloc (sizeof (struct dlist_));

	insert(list, &a, 0);
	insert(list, &b, 0);
	insert(list, &c, 0);

	node *current_item = list->head;
	node *prev = NULL;

	while (current_item != NULL) {
		printf("%d\n", *((int*)current_item->thing));
		node* temp = current_item;
		current_item = (node*) ((uintptr_t)(current_item->ptr) ^ (uintptr_t)prev);
		prev = temp;
	}

	printf("%d\n", *((int*)search(list, (void*)&d)));

	return 0;
}
