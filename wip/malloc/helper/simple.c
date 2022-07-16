#include <stdlib.h>
#include <stdio.h>

int
main()
{
	size_t find = 0, size;
	for (unsigned i = 10; i--;)
	{
		size = rand() % 2048;
		void *ptr = malloc(size);
		free(ptr);
	}
}
