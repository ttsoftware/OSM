#include "tests/lib.h"

int main(void) {

	// 960 is the max number of ints. 
	// 3240 is then the maximum number of bytes available to the process.
	printf("4040%d\n",42);

	int x = 42;
	x = x;

	printf("%d\n", x);

	printf("42%d\n", x);

  	return 0;
}