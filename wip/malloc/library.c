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

#include "ft.h"

typedef struct
{
	size_t length;
	size_t allocated;
} block_header_t;

int malloc_count = 0, free_count = 0, realloc_count = 0;

void
free(void *ptr)
{
	ft_putstr(COLOR_RED "free(ptr=");
	ft_putnbr_hex((unsigned long)ptr);
	ft_putstr(")" COLOR_RESET "\n");

	if (!ptr)
		return;

	block_header_t *header = (void*)((char*)ptr - sizeof(block_header_t));
	munmap(header, header->length);

	errno = 0;

	++free_count;
}

void*
malloc(size_t size)
{
	ft_putstr(COLOR_GREEN "malloc(size=");
	ft_putnbr_dec(size);
	ft_putstr(") : ");

	size_t length = size + sizeof(block_header_t);

	void *ptr = mmap(NULL, length, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (ptr == MAP_FAILED)
	{
		ft_putstr(strerror(errno));
		ft_putstr(COLOR_RESET "\n");
		return (NULL);
	}

	ft_putnbr_hex((unsigned long)((char*)ptr + sizeof(block_header_t)));
	ft_putstr(COLOR_RESET "\n");

	errno = 0;

	block_header_t *header = memset(ptr, 0, sizeof(block_header_t));

	header->length = length;
	header->allocated = size;

	++malloc_count;

	return ((char*)ptr + sizeof(block_header_t));
}

void*
realloc(void *ptr, size_t size)
{
	ft_putstr(COLOR_YELLOW "realloc(ptr=");
	ft_putnbr_hex((unsigned long)ptr);
	ft_putstr(") : ");

	if (!ptr)
		return (malloc(0));

	void *new_ptr = malloc(size);
	if (!new_ptr)
		return (NULL);

	block_header_t *header = (void*)((char*)ptr - sizeof(block_header_t));

	memmove(new_ptr, ptr, header->allocated);
	free(ptr);

	errno = 0;

	++realloc_count;

	return (new_ptr);
}

static void __attribute__ ((destructor))
destructor(void)
{
	ft_putstr(COLOR_BLUE "malloc_count = ");
	ft_putnbr_dec(malloc_count);
	ft_putstr("\n");

	ft_putstr(COLOR_BLUE "free_count = ");
	ft_putnbr_dec(free_count);
	ft_putstr("\n");

	ft_putstr(COLOR_BLUE "realloc_count = ");
	ft_putnbr_dec(realloc_count);
	ft_putstr("\n");
}
