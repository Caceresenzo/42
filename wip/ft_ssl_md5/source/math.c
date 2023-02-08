/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 00:54:59 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/07 00:54:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <inttypes.h>

#include "ft_ssl.h"

unsigned left_rotate(unsigned x, unsigned nbits)
{
	return ((x << nbits) | (x >> (32 - nbits)));
}

unsigned right_rotate(unsigned x, unsigned nbits)
{
	return ((x >> nbits) | (x << (32 - nbits)));
}

unsigned endian_small_to_big(unsigned x)
{
	unsigned b0 = (x & 0xff) << 24;
	unsigned b1 = (x & 0xff00) << 8;
	unsigned b2 = (x & 0xff0000) >> 8;
	unsigned b3 = (x & 0xff000000) >> 24;

	return (b0 | b1 | b2 | b3);
}

unsigned long endian_small_to_big_long(unsigned long x)
{
	return (__builtin_bswap64(x));
}
