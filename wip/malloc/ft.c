/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 20:15:10 by ecaceres          #+#    #+#             */
/*   Updated: 2022/06/06 20:15:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

#include <stddef.h>
#include <string.h>
#include <sys/types.h>
#include <sys/unistd.h>

ssize_t
ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

ssize_t
ft_putunbr_fd(unsigned long n, size_t radix, int fd)
{
	ssize_t recursive = 0;

	if (n >= radix)
		recursive = ft_putunbr_fd(n / radix, radix, fd);

	if (recursive == -1)
		return (-1);

	return (recursive + ft_putchar_fd("0123456789abcdef"[n % radix], fd));
}

ssize_t
ft_putunbr_fd_dec(unsigned long n, int fd)
{
	return (ft_putunbr_fd(n, 10, fd));
}

ssize_t
ft_putunbr_fd_hex(unsigned long n, int fd)
{
	return (ft_putunbr_fd(n, 16, fd));
}

ssize_t
ft_putstr_fd(const char *str, int fd)
{
	return (write(fd, str, ft_strlen(str)));
}

size_t
ft_strlen(const char *str)
{
	if (!str)
		return (0);

	const char *start = str;

	while (*str)
		str++;

	return (str - start);
}
