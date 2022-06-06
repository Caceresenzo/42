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

void
xfree(void *ptr)
{
	ft_printf(COLOR_RED "free(ptr=%p)" COLOR_RESET "\n", ptr);

	if (!ptr)
		return;

	region_t *region = region_search(ptr);
	if (!region)
	{
		ft_putstr_fd("free: invalid pointer: region not found", 2);
		abort();
	}

	if (region->type == RT_LARGE)
	{
		region_destroy(region);
		return;
	}

	block_t *block = block_search(region, ptr);
	if (!block)
	{
		ft_putstr_fd("free: invalid pointer: block not found", 2);
		abort();
	}

	block_destroy(region, block);
}

int
main(int argc, char **argv)
{


	show_alloc_mem();

	char *a = xmalloc(400);
//	hello = xmalloc(32352000);
	char *b = xmalloc(500);
//	hello = xmalloc(1);

	show_alloc_mem();

	xfree(a);

	show_alloc_mem();

	xfree(b);

	show_alloc_mem();

	ft_printf("sizeof(region_t)=%l\n", sizeof(region_t));
	ft_printf("sizeof(block_t)=%l\n", sizeof(block_t));
}
