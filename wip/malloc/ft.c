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
#include <stdlib.h>
#include <signal.h>

void
ft_assert_abort(const char *filename, int line, const char *function, const char *code)
{
	ft_printf("%s:%d: %s: Assertion `%s' failed.\n", filename, line, function, code);
	abort();
}

int
ft_tolower(int c)
{
	if (ft_isupper(c))
		return (c + 0x20);
	return (c);
}

int
ft_isupper(int c)
{
	return (c >= 'A' && c <= 'Z');
}

ssize_t
ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

ssize_t
ft_putunbr_fd(unsigned long n, size_t radix, int fd, bool upper)
{
	static const char *alphabets[] = {
		"0123456789abcdef",
		"0123456789ABCDEF",
	};

	ssize_t recursive = 0;

	if (n >= radix)
		recursive = ft_putunbr_fd(n / radix, radix, fd, upper);

	if (recursive == -1)
		return (-1);

	const char *alphabet = alphabets[!!upper];
	return (recursive + ft_putchar_fd(alphabet[n % radix], fd));
}

ssize_t
ft_putunbr_fd_dec(unsigned long n, int fd)
{
	return (ft_putunbr_fd(n, 10, fd, false));
}

ssize_t
ft_putunbr_fd_hex(unsigned long n, int fd, bool upper)
{
	return (ft_putunbr_fd(n, 16, fd, upper));
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

int
ft_strcasecmp(const char *left, const char *right)
{
	for (;; left++, right++)
	{
		char a = ft_tolower((unsigned char)*left);
		char b = ft_tolower((unsigned char)*right);

		int diff = a - b;
		if (diff || !a || !b)
			return (diff);
	}

	return (0);
}
