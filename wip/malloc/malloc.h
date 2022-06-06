/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 22:12:11 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/06 22:12:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

void
free(void *ptr);

void*
malloc(size_t size);

void*
realloc(void *ptr, size_t size);

void
show_alloc_mem();

typedef enum region_type_e
{
	RT_TINY,
	RT_SMALL,
	RT_LARGE,
} region_type_t;

typedef struct sized_region_type_s
{
	region_type_t type;
	size_t length;
} sized_region_type_t;

typedef struct region_s
{
	size_t size;
	size_t free_size;
	region_type_t type;
	struct region_s *next;
	struct region_s *previous;
} region_t;

typedef struct block_s
{
	bool free;
	size_t size;
	struct block_s *next;
	struct block_s *previous;
} block_t;

region_t *g_region;

void*
region_get_start(region_t *region);

void*
region_get_end(region_t *region);

block_t*
region_get_first_block(region_t *region);

region_t*
region_create(size_t size);

region_t*
region_find_or_create(size_t size);

region_t*
region_search(void *ptr);

void
region_destroy(region_t *region);

const char*
region_type_to_string(region_type_t type);

void*
block_get_start(block_t *block);

void*
block_get_end(block_t *block);

block_t*
block_split(region_t *region, block_t *block, size_t size);

block_t*
block_find_or_create(region_t *region, size_t size);

block_t*
block_search(region_t *region, void *ptr);

void
block_destroy(region_t *region, block_t *block);

sized_region_type_t
region_estimate_length(size_t size);

#endif
