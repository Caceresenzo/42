/// from https://gist.github.com/stevenpray/10805318

#include <stdio.h>

int
main(void)
{
	for (unsigned int i = 1; i <= 100; i++)
	{
		if (i % 15 == 0)
		{
			printf("FizzBuzz\n");
		}
		else if (i % 3 == 0)
		{
			printf("Fizz\n");
		}
		else if (i % 5 == 0)
		{
			printf("Buzz\n");
		}
		else
		{
			printf("%u\n", i);
		}
	}
	return 0;
}
