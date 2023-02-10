/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 00:54:23 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/07 00:54:23 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ft_ssl.h"

// @formatter:off
static unsigned int s[64] = {
	7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
	4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
	6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,
};

static unsigned int K[64] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391,
};

static unsigned char PADDING[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
// @formatter:on

void md5_begin(md5_context_t *ctx)
{
	ctx->state.a = 0x67452301;
	ctx->state.b = 0xefcdab89;
	ctx->state.c = 0x98badcfe;
	ctx->state.d = 0x10325476;

	ctx->length = 0;
	ft_memset(ctx->buffer, 0, sizeof(ctx->buffer));
}

void md5_update(md5_context_t *ctx, const void *buf, size_t len)
{
	unsigned buffer_size;
	while (1)
	{
		buffer_size = ctx->length % 64;

		if (buffer_size + len >= 64)
		{
			unsigned copied = 64 - buffer_size;

			ft_memcpy(ctx->buffer + buffer_size, buf, copied);
			md5_transform(ctx, ctx->buffer);

			len -= copied;
			buf += copied;
			ctx->length += copied;
		}
		else
			break;
	}

	ft_memcpy(ctx->buffer + buffer_size, buf, len);
	ctx->length += len;
}

void md5_transform(md5_context_t *ctx, const unsigned char block[64])
{
#define and &
#define or |
#define not ~
#define xor ^
#define mod %

	unsigned int M[16];
	ft_memcpy(M, block, sizeof(M));

	unsigned A = ctx->state.a;
	unsigned B = ctx->state.b;
	unsigned C = ctx->state.c;
	unsigned D = ctx->state.d;

	for (unsigned i = 0; i < 64; ++i)
	{
		unsigned F;
		unsigned g;

		if (i <= 15)
		{
			F = (B and C) or ((not B) and D);
			g = i;
		}
		else if (i <= 31)
		{
			F = (D and B) or ((not D) and C);
			g = (5 * i + 1) mod 16;
		}
		else if (i <= 47)
		{
			F = B xor C xor D;
			g = (3 * i + 5) mod 16;
		}
		else if (i <= 63)
		{
			F = C xor (B or (not D));
			g = (7 * i) mod 16;
		}

		F = F + A + K[i] + M[g];
		A = D;
		D = C;
		C = B;
		B = B + ft_left_rotate(F, s[i]);
	}

	ctx->state.a += A;
	ctx->state.b += B;
	ctx->state.c += C;
	ctx->state.d += D;
}

void md5_end(md5_context_t *ctx, unsigned char digest[16])
{
	unsigned long total_length_bits = ctx->length * 8;
	unsigned char length_bits[8];
	ft_memcpy(length_bits, &total_length_bits, 8);

	unsigned length_mod = ctx->length % 64;
	unsigned padding_length;
	if (length_mod < 56)
		padding_length = 56 - length_mod;
	else
		padding_length = (64 + 56) - length_mod;

	md5_update(ctx, PADDING, padding_length);
	md5_update(ctx, length_bits, 8);

	ft_memcpy(digest, &ctx->state, sizeof(ctx->state));
}
