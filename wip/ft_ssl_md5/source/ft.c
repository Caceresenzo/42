/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 23:58:36 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/08 23:58:36 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

#include "ft_ssl.h"

size_t ft_strlen(const char *str)
{
	const char *start = str;

	while (*str)
		++str;

	return (str - start);
}

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			break;

		s1++;
		s2++;
	}

	return (*(unsigned char*)s1 - *(unsigned char*)s2);
}

void* ft_memset(void *b, int c, size_t len)
{
	unsigned char *ptr = b;

	while (len--)
	{
		*ptr = c;
		++ptr;
	}

	return (b);
}

void* ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char *to = dst;
	const unsigned char *from = src;

	while (n--)
	{
		*to = *from;
		++to;
		++from;
	}

	return (dst);
}

unsigned ft_rotl32(unsigned x, unsigned nbits)
{
	return ((x << nbits) | (x >> (32 - nbits)));
}

unsigned ft_rotr32(unsigned x, unsigned nbits)
{
	return ((x >> nbits) | (x << (32 - nbits)));
}

unsigned long ft_rotl64(unsigned long x, unsigned nbits)
{
	return ((x << nbits) | (x >> (64 - nbits)));
}

unsigned long ft_rotr64(unsigned long x, unsigned nbits)
{
	return ((x >> nbits) | (x << (64 - nbits)));
}

/* https://stackoverflow.com/a/2637138/7292958 */
unsigned ft_bswap32(unsigned x)
{
	x = ((x << 8) & 0xFF00FF00) | ((x >> 8) & 0xFF00FF);
	return ((x << 16) | (x >> 16));
}

/* https://stackoverflow.com/a/2637138/7292958 */
unsigned long ft_bswap64(unsigned long x)
{
	x = ((x << 8) & 0xFF00FF00FF00FF00ULL) | ((x >> 8) & 0x00FF00FF00FF00FFULL);
	x = ((x << 16) & 0xFFFF0000FFFF0000ULL) | ((x >> 16) & 0x0000FFFF0000FFFFULL);
	return ((x << 32) | (x >> 32));
}

