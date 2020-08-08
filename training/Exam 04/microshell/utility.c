/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 12:06:31 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/08 12:06:31 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void*
malloc_zeros(size_t size)
{
	char *mem = malloc(size);

	if (mem)
		for (size_t i = 0; i < size; i++)
			mem[i] = 0;

	return (mem);
}

size_t
ft_strlen(char *str)
{
	char *start = str;

	while (*str)
		str++;

	return (str - start);
}

void
ft_putstr(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}
