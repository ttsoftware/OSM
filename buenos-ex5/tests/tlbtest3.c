#include "tests/lib.h"

int main(void) {

	// nooooo...
	heap_init();

	int y = 1;

	void* some_block = malloc(sizeof y);
	malloc((sizeof y)*10);

	free(some_block);

	some_block = malloc(sizeof y);

	// man kan ikke derefence void pointer, så hvordan demonstrerer vi at det virker?
	// vi synes det virker :)

	return 0;
}