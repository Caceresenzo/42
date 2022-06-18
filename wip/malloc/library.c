/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   library.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 18:48:53 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/06 18:48:53 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stddef.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/mman.h>
#include <assert.h>
#include <stdio.h>

#include "ft.h"
#include "malloc.h"

//extern void*
//__libc_malloc(size_t size);
//
//extern void
//__libc_free(void*);
//
//extern void*
//__libc_realloc(void *ptr, size_t size);
//
//void*
//malloc(size_t size)
//{
//	ft_printf(COLOR_GREEN "malloc(size=%l): ", size);
//
//	void *ptr = __libc_malloc(size);
//
//	ft_printf("%p" COLOR_RESET "\n", ptr);
//
//	return (ptr);
//}
//
//void
//free(void *ptr)
//{
//	ft_printf(COLOR_RED "free(ptr=%p)" COLOR_RESET "\n", ptr);
//
//	__libc_free(ptr);
//}
//
//void*
//realloc(void *ptr, size_t size)
//{
//	ft_printf(COLOR_YELLOW "realloc(ptr=%p, size=%l): ", ptr, size);
//
//	void *new_ptr = __libc_realloc(ptr, size);
//
//	ft_printf("%p" COLOR_RESET "\n", new_ptr);
//
//	return (new_ptr);
//}

#include <execinfo.h>
#include <stdio.h>
#include <unistd.h>

static bool g_log = true;
static bool g_removed = false;

void
print_trace(void)
{
	void *trace[1024];
	char **messages = (char**)NULL;
	int i, trace_size = 0;

	g_log = false;

	trace_size = backtrace(trace, 1024);
	messages = backtrace_symbols(trace, trace_size);

	ft_printf("[bt] Execution path:\n");
	for (i = 1; i < trace_size; ++i)
	{
		ft_printf("[bt] #%d %s:\n[bt]        ", i, messages[i]);

		/* find first occurence of '(' or ' ' in message[i] and assume
		 * everything before that is the file name. (Don't go beyond 0 though
		 * (string terminator)*/
		int p = 0;
		while (messages[i][p] != '(' && messages[i][p] != ' ' && messages[i][p] != 0)
			++p;

		int pe = 0;
		while (messages[i][p + pe] != ')' && messages[i][p + pe] != 0)
			++pe;

		char syscom[256];
		sprintf(syscom, "addr2line %.*s -e %.*s", pe - 1, messages[i] + p + 1, p, messages[i]);
//		ft_printf("%s: ", syscom);
		//last parameter is the file name of the symbol
		system(syscom);
	}

//	size_t i, size;
//	enum Constexpr
//	{
//		MAX_SIZE = 1024
//	};
//	void *array[MAX_SIZE];
//	size = backtrace(array, MAX_SIZE);
//	backtrace_symbols_fd(array, size, STDOUT_FILENO);
//	ft_printf("\n");

	g_log = true;
}

void
_hook()
{
//	if (!g_removed)
//	{
//		int res = unsetenv("LD_PRELOAD");
//		ft_printf("unsetenv=%d\n", res);
//		g_removed = true;
//	}
}

extern region_t *g_region;

region_t*
region_get(const char *caller, void *ptr)
{
	region_t *region = region_search(ptr);

	if (!region)
	{
		ft_putstr_fd(caller, 2);
		ft_putstr_fd(": invalid pointer: region not found\n", 2);
		show_alloc_mem();

//		region_t *region = g_region;
//		while (region)
//		{
//			ft_printf("REGION %p (start=%p)", region, region_get_start(region));
//			if (region_get_start(region) <= ptr && ptr <= region_get_end(region))
//				ft_printf("  <<  >>", region, region_get_start(region));
//			else
//				ft_printf("\n");
//
//			region = region->next;
//		}

//		show_alloc_mem	();
		abort();
	}

	return (region);
}

block_t*
block_get_free(const char *caller, region_t *region, void *ptr)
{
	block_t *block = block_search(region, ptr);

	if (!block)
	{
		ft_putstr_fd(caller, 2);
		ft_putstr_fd(": invalid pointer: block not found\n", 2);
		abort();
	}

	if (block->free)
	{
		ft_putstr_fd(caller, 2);
		ft_putstr_fd(": double free\n", 2);
		abort();
	}

	return (block);
}

void*
malloc(size_t size)
{
	_hook();

	if (g_log)
		ft_printf(COLOR_GREEN "malloc(size=%l): ", size);

	size = MEMORY_ALIGN(size);

	region_t *region = region_find_or_create(size);
	if (!region)
		return (NULL);

	void *ptr;

	if (region->type == RT_LARGE)
		ptr = region_get_start(region);
	else
	{
		block_t *block = block_find_and_split(region, size);
		assert(block != NULL);

		ptr = block_get_start(block);
	}

	if (g_log)
		ft_printf("%p" COLOR_RESET "\n", ptr);

	return (ptr);
}

void
region_or_block_destroy(region_t *region, block_t *block)
{
	if (region->type == RT_LARGE)
		region_destroy(region);
	else
		block_destroy(region, block);
}

void
free(void *ptr)
{
	_hook();

	if (g_log)
		ft_printf(COLOR_RED "free(ptr=%p)" COLOR_RESET "\n", ptr);

//	if (ptr)
//	{
//		region_t *reg = (void*)((char*)ptr - sizeof(region_t));
//
//		if (reg->magic != REGION_MAGIC)
//		{
//			ft_printf("REGION %p (start=%p)\n", reg, region_get_start(reg));
//			ft_printf("  magic %d\n", (int)reg->magic);
//			ft_printf("  magic ok? %b\n", reg->magic == REGION_MAGIC);
//			ft_printf("  size %l\n", reg->size);
//			ft_printf("  free_size %l\n", reg->free_size);
//			ft_printf("  type %s (%d)\n", region_type_to_string(reg->type), reg->type);
//
//			print_trace();
////			show_alloc_mem();
//		}
//	}

	if (!ptr)
		return;

	region_t *region = region_get("free", ptr);
	block_t *block = NULL;

	if (region && region->type != RT_LARGE)
		block = block_get_free("free", region, ptr);

	if (region)
		region_or_block_destroy(region, block);
}

void*
realloc(void *ptr, size_t size)
{
	_hook();

	if (g_log)
		ft_printf(COLOR_YELLOW "realloc(ptr=%p, size=%l): ", ptr, size);

	size = MEMORY_ALIGN(size);

	if (!ptr)
		return (malloc(size));

	size_t length = 0;

	region_t *region = region_get("realloc", ptr);
	block_t *block = NULL;

	if (region->type == RT_LARGE)
		length = region->size;
	else
	{
		block = block_get_free("realloc", region, ptr);
		length = block->size;
	}

	ft_printf(COLOR_YELLOW "length=%l, ", length);

	size_t to_move = MIN(length, size);
	ft_printf(COLOR_YELLOW "move=%l: " COLOR_RESET, to_move);

	void *new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);

	memset(new_ptr, 0xAA, size);

	memmove(new_ptr, ptr, to_move);

	region_or_block_destroy(region, block);

	return (new_ptr);
}

void*
calloc(size_t nmemb, size_t size)
{
	const size_t total = nmemb * size;

	void *ptr = malloc(total);
	if (ptr)
		memset(ptr, 0, total);

	return (ptr);
}

void*
reallocarray(void *ptr, size_t nmemb, size_t size)
{
	return (realloc(ptr, nmemb * size));
}
