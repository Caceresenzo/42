/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   region.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:13:15 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/06 22:13:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <assert.h>
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <string.h>
#include <sys/errno.h>
#include <sys/mman.h>
#include <sys/unistd.h>

#include "ft.h"
#include "malloc.h"

region_t *g_region = NULL;

region_t*
region_get_first(void)
{
	return (g_region);
}

void*
region_get_start(region_t *region)
{
	return ((char*)region + sizeof(region_t));
}

void*
region_get_end(region_t *region)
{
	return ((char*)region_get_start(region) + region->size);
}

block_t*
region_get_first_block(region_t *region)
{
	return (region_get_start(region));
}

sized_region_type_t
region_estimate_length(size_t size)
{
	sized_region_type_t sized;
	size_t page_size = getpagesize();

	if (size < page_size * 4)
	{
		sized.type = RT_TINY;
		sized.length = page_size * 8;
	}
	else if (size < page_size * 32)
	{
		sized.type = RT_SMALL;
		sized.length = page_size * 32;
	}
	else
	{
		sized.type = RT_LARGE;
		sized.length = ALIGN_MIN(size + sizeof(region_t), page_size, page_size);
	}

	return (sized);
}

region_t*
region_create(size_t size)
{
	sized_region_type_t sized = region_estimate_length(size);

	region_t *region = mmap(NULL, sized.length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (region == MAP_FAILED)
		return (NULL);

	memset(region, 0, sizeof(region_t));
	region->magic = REGION_MAGIC;
	region->size = sized.length - sizeof(region_t);
	region->type = sized.type;

	if (sized.type != RT_LARGE)
	{
		region->free_size = sized.length - sizeof(region_t) - sizeof(block_t);

		block_t *block = region_get_first_block(region);
		memset(block, 0, sizeof(block_t));
		block->magic = BLOCK_MAGIC;
		block->free = true;
		block->size = region->free_size;
	}

	return (region);
}

void
region_insert(region_t *region)
{
	region_t *iterator = g_region;
	region_t *previous = NULL;

	for (; iterator; iterator = iterator->next)
	{
		region_t *previous = iterator->previous;

		if (region > previous && region < iterator)
			break;

		previous = iterator;
	}

	if (iterator)
	{
		if (iterator->previous)
		{
			iterator->previous->next = region;
			region->previous = iterator->previous;

			iterator->previous = region;
			region->next = iterator;
		}
		else /* first */
		{
			region->next = g_region;
			region->next->previous = region;

			g_region = region;
		}
	}
	else if (previous) /* end */
	{
		previous->next = region;
		region->previous = previous;
	}
	else
	{
		assert(g_region == NULL);
		g_region = region;
	}
}

region_t*
region_find_or_create(size_t size)
{
	region_t *region = g_region;

	while (region)
	{
		if (region->free_size >= size && block_find(region, size))
			return (region);

		region = region->next;
	}

	region = region_create(size);
	if (!region)
		return (NULL);

	region_insert(region);

	return (region);
}

region_t*
region_search(void *ptr)
{
	if (!ptr)
		return (NULL);

	region_t *region = g_region;

	while (region)
	{
		assert(region->magic == REGION_MAGIC);

		void *start = region_get_start(region);

		if (region->type == RT_LARGE)
		{
			if (start == ptr)
				return (region);
		}
		else
		{
			if (start <= ptr && ptr <= region_get_end(region))
				return (region);
		}

		region = region->next;
	}

	return (NULL);
}

void
region_destroy(region_t *region)
{
	if (region->previous)
		region->previous->next = region->next;
	else
		g_region = region->next;

	if (region->next)
		region->next->previous = region->previous;

	munmap(region, region->size + sizeof(region_t));
}

const char*
region_type_to_string(region_type_t type)
{
	if (type == RT_TINY)
		return ("TINY");

	if (type == RT_SMALL)
		return ("SMALL");

	if (type == RT_LARGE)
		return ("LARGE");

	return ("UNKNOWN");
}
