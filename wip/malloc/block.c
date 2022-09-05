/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   block.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:13:10 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/06 22:13:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <sys/unistd.h>

#include "malloc.h"
#include "ft.h"

void*
block_get_start(block_t *block)
{
	return ((char*)block + sizeof(block_t));
}

void*
block_get_end(block_t *block)
{
	return ((char*)block_get_start(block) + block->size);
}

block_t*
block_split(region_t *region, block_t *block, size_t size)
{
	block->free = false;

	if (block->size >= size + sizeof(block_t) + 1)
	{
		block_t *second = (void*)((char*)block_get_start(block) + size);
		memset(second, 0, sizeof(block_t));
		second->magic = BLOCK_MAGIC;
		second->free = true;
		second->size = block->size - size - sizeof(block_t);

		/* prevent zero size block */
		ASSERT(second->size);

		if (block->next)
		{
			second->next = block->next;
			second->next->previous = second;
		}

		block->next = second;
		second->previous = block;

		block->size = size;
		region->free_size -= size + sizeof(block_t);

		return (block);
	}

	region->free_size -= block->size;

	/* not enough space for next block, so merge it */
	return (block);
}

block_t*
block_find(region_t *region, size_t size)
{
	block_t *block = region_get_first_block(region);

	while (block)
	{
		ASSERT(block->magic == BLOCK_MAGIC);

		if (block->free && block->size >= size)
			return (block);

		block = block->next;
	}

	return (NULL);
}

block_t*
block_find_and_split(region_t *region, size_t size)
{
	block_t *block = block_find(region, size);

	if (block)
		return (block_split(region, block, size));

	show_alloc_mem();
	return (NULL);
}

block_t*
block_search(region_t *region, void *ptr)
{
	block_t *block = region_get_first_block(region);

	while (block)
	{
		if (block_get_start(block) == ptr)
			return (block);

		block = block->next;
	}

	return (NULL);
}

void
block_destroy(region_t *region, block_t *block)
{
	block->free = true;
	region->free_size += block->size;

	block_t *previous = block->previous;
	block_t *next = block->next;

	if (previous && previous->free)
	{
		region->free_size += sizeof(block_t);
		previous->size += block->size + sizeof(block_t);

		block = previous;
		block->next = next;
	}

	if (next && next->free)
	{
		region->free_size += sizeof(block_t);
		block->size += next->size + sizeof(block_t);

		block->next = next->next;
	}

	if (block->previous)
		block->previous->next = block;

	if (block->next)
		block->next->previous = block;
}
