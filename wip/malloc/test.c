#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char **argv)
{
	char *hello = malloc(10);
	free(hello);
}
