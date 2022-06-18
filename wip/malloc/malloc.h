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

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define ALIGN(value, alignment) ((value) + (-(value) & ((alignment) - 1)))
#define ALIGN_MIN(value, alignment, min) MAX(ALIGN(value, alignment), min)

#define MEMORY_ALIGNMENT (sizeof(void*) * 2)
#define MEMORY_ALIGN(value) ALIGN(value, MEMORY_ALIGNMENT)
#define MEMORY_ALIGN_MIN(value, min) ALIGN_MIN(value, MEMORY_ALIGNMENT, min)

#define TO_ENV_VAR_NAME(suffix) ("MALLOC_" suffix)

void
free(void *ptr);

void*
malloc(size_t size);

void*
realloc(void *ptr, size_t size);

void*
calloc(size_t nmemb, size_t size);

void*
reallocarray(void *ptr, size_t nmemb, size_t size);

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

#define REGION_MAGIC (42)

typedef struct region_s
{
	char magic;
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

typedef struct
{
	bool log;
	bool log_colored;
	bool check_magic;
} tunes_t;

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
block_find(region_t *region, size_t size);

block_t*
block_find_and_split(region_t *region, size_t size);

block_t*
block_search(region_t *region, void *ptr);

void
block_destroy(region_t *region, block_t *block);

sized_region_type_t
region_estimate_length(size_t size);

const tunes_t*
tune_get();

bool
tune_find_boolean(const char *key, bool default_value);

void
tune_initialize(tunes_t *tunes);

void
free_impl(const char *caller, void *ptr);

void*
malloc_impl(const char *caller, size_t size);

void*
realloc_impl(const char *caller, void *ptr, size_t size);

void*
calloc_impl(const char *caller, size_t nmemb, size_t size);

void*
reallocarray_impl(const char *caller, void *ptr, size_t nmemb, size_t size);

#endif
