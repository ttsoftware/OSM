#include "tests/lib.h"

int main(void) {

	// 960 is the max number of ints. 
	// 3240 is then the maximum number of bytes available to the process.
	int big_ass_array[961]; 

	big_ass_array[1] = 3;
	big_ass_array[2] = 2;
	big_ass_array[3] = 1;

	int stalin = big_ass_array[1];
	stalin = stalin;

	// HVORFOR FEJLER DEN KUN VED PRINT?
	printf("%d\n", stalin);

  	return 0;
} 
