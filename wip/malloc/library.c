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

#include "ft.h"
#include "malloc.h"

//int malloc_count = 0, free_count = 0, realloc_count = 0;

//void*
//malloc(size_t size)
//{
//	ft_printf(COLOR_GREEN "malloc(size=%l): ", size);
//
//	region_t *region = region_find_or_create(size);
//	if (!region)
//		return (NULL);
//
//	block_t *block = block_find_or_create(region, size);
//	assert(block != NULL);
//
//	void *ptr = block_get_start(block);
//
//	ft_printf("%p" COLOR_RESET "\n", ptr);
//
//	++malloc_count;
//
//	return (ptr);
//}

//void
//free(void *ptr)
//{
//	ft_printf(COLOR_RED "free(ptr=%p)" COLOR_RESET "\n", ptr);
//
//	if (!ptr)
//		return;
//
//	block_header_t *header = (void*)((char*)ptr - sizeof(block_header_t));
//	munmap(header, header->length);
//
//	errno = 0;
//
//	++free_count;
//}
//
//void*
//realloc(void *ptr, size_t size)
//{
//	ft_printf(COLOR_YELLOW "realloc(ptr=%p): ", ptr);
//
//	if (!ptr)
//		return (malloc(0));
//
//	void *new_ptr = malloc(size);
//	if (!new_ptr)
//		return (NULL);
//
//	block_header_t *header = (void*)((char*)ptr - sizeof(block_header_t));
//
//	memmove(new_ptr, ptr, header->allocated);
//	free(ptr);
//
//	errno = 0;
//
//	++realloc_count;
//
//	return (new_ptr);
//}

//static void __attribute__ ((destructor))
//destructor(void)
//{
//	ft_printf(COLOR_BLUE "malloc_count = %d" COLOR_RESET "\n", malloc_count);
//	ft_printf(COLOR_BLUE "free_count = %d" COLOR_RESET "\n", free_count);
//	ft_printf(COLOR_BLUE "realloc_count = %d" COLOR_RESET "\n", realloc_count);
//}
