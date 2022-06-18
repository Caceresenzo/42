#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>

#include "ft.h"
#include "malloc.h"

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

	(void)reallocarray("qsd", 1, 2);

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
