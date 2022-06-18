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


#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

#include "ft.h"
#include "malloc.h"

static bool g_log = false;

void*
malloc(size_t size)
{
	if (g_log)
		ft_printf(COLOR_GREEN "malloc(size=%l): ", size);

	void *ptr = malloc_impl(__FUNCTION__, size);

	if (g_log)
		ft_printf("%p" COLOR_RESET "\n", ptr);

	return (ptr);
}

void
free(void *ptr)
{
	if (g_log)
		ft_printf(COLOR_RED "free(ptr=%p)", ptr);

	free_impl(__FUNCTION__, ptr);

	if (g_log)
		ft_printf(COLOR_RESET "\n");
}

void*
realloc(void *ptr, size_t size)
{
	if (g_log)
		ft_printf(COLOR_GREEN "realloc(ptr=%p, size=%l): ", ptr, size);

	void *new_ptr = realloc_impl(__FUNCTION__, ptr, size);

	if (g_log)
		ft_printf("%p" COLOR_RESET "\n", new_ptr);

	return (new_ptr);
}

void*
calloc(size_t nmemb, size_t size)
{
	if (g_log)
		ft_printf(COLOR_GREEN "calloc(nmemb=%l, size=%l): ", nmemb, size);

	void *ptr = calloc_impl(__FUNCTION__, nmemb, size);

	if (g_log)
		ft_printf("%p" COLOR_RESET "\n", ptr);

	return (ptr);
}

void*
reallocarray(void *ptr, size_t nmemb, size_t size)
{
	if (g_log)
		ft_printf(COLOR_GREEN "reallocarray(ptr=%p, nmemb=%l, size=%l): ", ptr, nmemb, size);

	void *new_pre = realloc_impl(__FUNCTION__, ptr, nmemb * size);

	if (g_log)
		ft_printf("%p" COLOR_RESET "\n", new_pre);

	return (new_pre);
}
