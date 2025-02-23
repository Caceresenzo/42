/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 18:16:46 by ecaceres          #+#    #+#             */
/*   Updated: 2022/05/21 18:16:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft.h"

#include <stddef.h>
#include <unistd.h>

int
ft_islower(int c)
{
	return (c >= 'a' && c <= 'z');
}

int
ft_toupper(int c)
{
	if (ft_islower(c))
		return (c - 0x20);

	return (c);
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

size_t
ft_strnlen(const char *str, size_t max)
{
	if (!str)
	{
		if (!max)
			return (-1);

		return (0);
	}

	const char *start = str;
	while (max && *str)
	{
		str++;
		--max;
	}

	if (max == 0)
		return (-1);

	return (str - start);
}

int
ft_strncmp(const char *s1, const char *s2, size_t n)
{
	if (n == 0)
		return (0);
	if (s1 == s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);

	while (n > 0 && *s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
		n--;
	}

	if (n == 0)
		return (0);

	return (*(unsigned char*)s1 - *(unsigned char*)s2);
}

int
ft_strcmp(const char *s1, const char *s2)
{
	if (s1 == s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);

	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
	}

	return (*(unsigned char*)s1 - *(unsigned char*)s2);
}

bool
ft_strstartswith(const char *str, const char *prefix)
{
	if (!str)
		return (false);

	return (ft_strncmp(str, prefix, ft_strlen(prefix)) == 0);
}

void*
ft_calloc(size_t count, size_t size)
{
	size_t required = count * size;

	void *array = malloc(required);
	if (array)
		ft_memset(array, 0, required);

	return (array);
}

void*
ft_memset(void *src, int c, size_t n)
{
	if (!src)
		return (NULL);

	unsigned char *ptr = src;
	while (n--)
		*ptr++ = (unsigned char)c;

	return (src);
}

ssize_t
ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

ssize_t
ft_putstr_fd(const char *s, int fd)
{
	return (write(fd, s, ft_strlen(s)));
}

void
ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

int
ft_memcmp(const void *s1, const void *s2, size_t n)
{
	if (n == 0)
		return (0);
	if (s1 == s2)
		return (0);
	if (!s1)
		return (-1);
	if (!s2)
		return (1);

	unsigned char *array1 = (unsigned char*)s1;
	unsigned char *array2 = (unsigned char*)s2;

	while ((*array1 == *array2) && n - 1 > 0)
	{
		array1++;
		array2++;
		n--;
	}

	return (*array1 - *array2);
}

static size_t
ft_itoa_nsize(long number, size_t radix)
{
	size_t size = (number < 0 ? 1 : 0);

	while (1)
	{
		number /= radix;

		size++;

		if (number == 0)
			break;
	}

	return (size);
}

char*
ft_itoa(long n, char *string, int radix)
{
	long long number;
	size_t size;

	number = n;
	size = ft_itoa_nsize(n, radix);
	if (number < 0)
	{
		string[0] = '-';
		number *= -1;
	}
	string[size] = '\0';
	while (1)
	{
		string[size - 1] = "0123456789abcdef"[(number % radix)];
		number /= radix;
		size--;
		if (number == 0)
			break;
	}
	return (string);
}

char*
ft_strchr(const char *s, int c)
{
	return (ft_memchr(s, c, ft_strlen(s) + 1));
}

void*
ft_memchr(const void *s, int c, size_t n)
{
	const char *ptr = s;

	while (n--)
	{
		if (*ptr == c)
			return ((void*)ptr);
		++ptr;
	}

	return (NULL);
}
