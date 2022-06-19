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
	const char *start;

	start = str;
	if (str)
		while (*str)
			str++;
	return (str - start);
}

int
ft_strncmp(const char *s1, const char *s2, size_t n)
{
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
	while (*s1 != '\0' && *s2 != '\0')
	{
		if (*s1 != *s2)
			break;
		s1++;
		s2++;
	}
	return (*(unsigned char*)s1 - *(unsigned char*)s2);
}

int
ft_strcasecmp(const char *left, const char *right)
{
	for (;; left++, right++)
	{
		char a = ft_toupper((unsigned char)*left);
		char b = ft_toupper((unsigned char)*right);

		int diff = a - b;
		if (diff || !a || !b)
			return (diff);
	}

	return (0);
}

bool
ft_strstartswith(const char *str, const char *prefix)
{
	if (!str)
		return (false);
	return (ft_strncmp(str, prefix, ft_strlen(prefix)) == 0);
}

void*
ft_memchr(const void *s, int c, size_t n)
{
	size_t index;

	index = 0;
	while (index < n)
	{
		if (((unsigned char*)s)[index] == (unsigned char)c)
			return (((unsigned char*)s) + index);
		index++;
	}
	return (NULL);
}

void*
ft_calloc(size_t count, size_t size)
{
	void *array;
	size_t required;

	required = count * size;
	array = malloc(required);
	if (array)
		ft_memset(array, 0, required);
	return (array);
}

void*
ft_memset(void *src, int c, size_t n)
{
	unsigned char *ptr;

	if ((ptr = src))
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
	unsigned char *array1;
	unsigned char *array2;

	if (n == 0)
		return (0);
	array1 = (unsigned char*)s1;
	array2 = (unsigned char*)s2;
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
	size_t size;

	size = (number < 0 ? 1 : 0);
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
