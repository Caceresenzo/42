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

#include <assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <sys/unistd.h>

#include "malloc.h"

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
		second->free = true;
		second->size = block->size - size - sizeof(block_t);

		/* prevent zero size block */
		assert(second->size);

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
block_find_or_create(region_t *region, size_t size)
{
	block_t *block = region_get_first_block(region);

	while (block)
	{
		if (block->free && block->size >= size)
			return (block_split(region, block, size));

		block = block->next;
	}

	return (NULL);
}
