/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   impl.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:44:37 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/18 19:44:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "ft.h"
#include "malloc.h"

static region_t*
region_get(const char *caller, void *ptr)
{
	region_t *region = region_search(ptr);

	if (!region)
	{
		ft_putstr_fd(caller, 2);
		ft_putstr_fd(": invalid pointer: region not found\n", 2);
		abort();
	}

	return (region);
}

static block_t*
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

static void
region_or_block_destroy(region_t *region, block_t *block)
{
	if (region->type == RT_LARGE)
		region_destroy(region);
	else
		block_destroy(region, block);
}

void
free_impl(const char *caller, void *ptr)
{
	if (!ptr)
		return;

	region_t *region = region_get(caller, ptr);
	block_t *block = NULL;

	if (region->type != RT_LARGE)
		block = block_get_free(caller, region, ptr);

	region_or_block_destroy(region, block);
}

void*
malloc_impl(const char *caller, size_t size)
{
	size = MEMORY_ALIGN(size);

	region_t *region = region_find_or_create(size);
	if (!region)
		return (NULL);

	if (region->type == RT_LARGE)
		return (region_get_start(region));

	block_t *block = block_find_and_split(region, size);
	assert(block != NULL);

	return (block_get_start(block));

	(void)caller;
}

void*
realloc_impl(const char *caller, void *ptr, size_t size)
{
	size = MEMORY_ALIGN(size);

	if (!ptr)
		return (malloc_impl(caller, size));

	size_t length = 0;

	region_t *region = region_get(caller, ptr);
	block_t *block = NULL;

	if (region->type == RT_LARGE)
		length = region->size;
	else
	{
		block = block_get_free(caller, region, ptr);
		length = block->size;
	}

	void *new_ptr = malloc_impl(caller, size);
	if (!new_ptr)
		return (NULL);

	memset(new_ptr, 0xAA, size);

	size_t to_move = MIN(length, size);
	memmove(new_ptr, ptr, to_move);

	region_or_block_destroy(region, block);

	return (new_ptr);
}

void*
calloc_impl(const char *caller, size_t nmemb, size_t size)
{
	const size_t total = nmemb * size;

	void *ptr = malloc_impl(caller, total);
	if (ptr)
		memset(ptr, 0, total);

	return (ptr);
}

void*
reallocarray_impl(const char *caller, void *ptr, size_t nmemb, size_t size)
{
	return (realloc_impl(caller, ptr, nmemb * size));
}
