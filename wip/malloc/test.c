#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#include "ft.h"
#include "malloc.h"

//void*
//xmalloc(size_t size)
//{
//	ft_printf(COLOR_GREEN "malloc(size=%l): ", size);
//
//	region_t *region = region_find_or_create(size);
//	if (!region)
//		return (NULL);
//
//	void *ptr;
//
//	if (region->type == RT_LARGE)
//		ptr = region_get_start(region);
//	else
//	{
//		block_t *block = block_find_or_create(region, size);
//		assert(block != NULL);
//
//		ptr = block_get_start(block);
//	}
//
//	ft_printf("%p" COLOR_RESET "\n", ptr);
//
//	return (ptr);
//}
//
//void
//xfree(void *ptr)
//{
//	ft_printf(COLOR_RED "free(ptr=%p)" COLOR_RESET "\n", ptr);
//
//	if (!ptr)
//		return;
//
//	region_t *region = region_search(ptr);
//	if (!region)
//	{
//		ft_putstr_fd("free: invalid pointer: region not found\n", 2);
//		show_alloc_mem();
//		abort();
//	}
//
//	if (region->type == RT_LARGE)
//	{
//		region_destroy(region);
//		/**/show_alloc_mem();
//		return;
//	}
//
//	block_t *block = block_search(region, ptr);
//	if (!block)
//	{
//		ft_putstr_fd("free: invalid pointer: block not found\n", 2);
//		show_alloc_mem();
//		abort();
//	}
//
//	if (block->free)
//	{
//		ft_putstr_fd("free: double free\n", 2);
//		show_alloc_mem();
//		abort();
//	}
//
//	block_destroy(region, block);
//	/**/show_alloc_mem();
//}
//
//static size_t
//realloc_get_length(void *ptr)
//{
//	size_t length = 0;
//	region_t *region = NULL;
//	block_t *block = NULL;
//
//	region = region_search(ptr);
//	if (!region)
//	{
//		ft_putstr_fd("realloc: invalid pointer: region not found\n", 2);
//		abort();
//	}
//
//	if (region->type == RT_LARGE)
//		length = region->size;
//	else
//	{
//		block = block_search(region, ptr);
//		if (!block)
//		{
//			ft_putstr_fd("realloc: invalid pointer: block not found\n", 2);
//			abort();
//		}
//
//		if (block->free)
//		{
//			ft_putstr_fd("realloc: double free\n", 2);
//			abort();
//		}
//
//		length = block->size;
//	}
//}
//
//void*
//xrealloc(void *ptr, size_t size)
//{
//	ft_printf(COLOR_YELLOW "realloc(ptr=%p): ", ptr);
//
//	if (!ptr)
//		return (xmalloc(size));
//
//	size_t length = realloc_get_length(ptr);
//
//	void *new_ptr = xmalloc(size);
//	if (!new_ptr)
//		return (NULL);
//
//# define MIN(a, b) (((a) < (b)) ? (a) : (b))
//	memmove(new_ptr, ptr, MIN(length, size));
//
//	xfree(ptr);
//
//	return (new_ptr);
//}

#include <assert.h>

int
main(int argc, char **argv)
{
	assert(sizeof(region_t) % 8 == 0);
	assert(sizeof(block_t) % 8 == 0);

//	void *ptr = realloc(0x0, 4096);
	for (int i = 0; i < 15; ++i) {
		malloc(i);
	}
//	free(ptr);
//	puts("hello");
	show_alloc_mem();

	ft_printf("sizeof(region_t)=%l\n", sizeof(region_t));
	ft_printf("sizeof(block_t)=%l\n", sizeof(block_t));

#define EXPECT_EQ(a, b) assert(a == b)

	EXPECT_EQ(0, ALIGN(0U, 16));
	EXPECT_EQ(16, ALIGN_MIN(0U, 16, 16));
	EXPECT_EQ(16U, ALIGN(1U, 16));
	EXPECT_EQ(8U, ALIGN(5U, 8U));
	EXPECT_EQ(8U, ALIGN(7U, 8U));
	EXPECT_EQ(64U, ALIGN_MIN(7U, 8U, 64U));

	EXPECT_EQ(0, ALIGN(0, 16));
	EXPECT_EQ(16, ALIGN(1, 16));
	EXPECT_EQ(8, ALIGN_MIN(8, 8, 8));
	EXPECT_EQ(8, ALIGN_MIN(7, 8, 8));
	EXPECT_EQ(64, ALIGN_MIN(7, 8, 64));
}
