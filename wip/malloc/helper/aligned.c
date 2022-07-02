#include <stdlib.h>
#include <stdio.h>

int
main()
{
	size_t find = 0, size;
	for (unsigned i = 1000000; i--;)
	{
		if (i % 100000 == 0)
			printf("%d\n", i / 10000);
		if (size = rand() & 127)
		{
			size_t ptr = (size_t)malloc(size);

			if (ptr % 8 != 0)
				printf("err: %lu\n", ptr);
//			else
//				printf("%p\n", ptr);

			find |= ptr;
			free((void*)ptr);
		}
	}
	char bits = 0;
	for (; !(find & 1); find >>= 1, ++bits)
		;
	printf("%d", (int)bits);
}
