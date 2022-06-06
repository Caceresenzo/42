#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>

#include "ft.h"
#include "malloc.h"

void*
xmalloc(size_t size)
{
	ft_printf(COLOR_GREEN "malloc(size=%l): ", size);

	region_t *region = region_find_or_create(size);
	if (!region)
		return (NULL);

	void *ptr;

	if (region->type == RT_LARGE)
		ptr = region_get_start(region);
	else
	{
		block_t *block = block_find_or_create(region, size);
		assert(block != NULL);

		ptr = block_get_start(block);
	}

	ft_printf("%p" COLOR_RESET "\n", ptr);

	return (ptr);
}

int
main(int argc, char **argv)
{
	char *hello = xmalloc(32352000);
	hello = xmalloc(3265);
	hello = xmalloc(13015);
	hello = xmalloc(1);

	show_alloc_mem();

//	free(hello);
}
