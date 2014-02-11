#include "lib/dlist.h"
#include "kernel/kmalloc.h"

int main(void)
{

	int a = 1;
	int b = 2;
	int c = 3;

	struct dlist_ *list = (struct dlist_ *) kmalloc (sizeof (struct dlist_));

	insert(list, &a, 0);
	insert(list, &b, 0);
	insert(list, &c, 0);

	return 0;
}
