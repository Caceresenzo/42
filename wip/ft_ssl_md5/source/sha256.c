/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 00:57:49 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/07 00:57:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

// @formatter:off
static unsigned k[64] = {
	   0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	   0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	   0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	   0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
	   0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	   0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	   0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	   0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};
// @formatter:on

void sha256_begin(sha256_context_t *ctx)
{
	ctx->state.h[0] = 0x6a09e667;
	ctx->state.h[1] = 0xbb67ae85;
	ctx->state.h[2] = 0x3c6ef372;
	ctx->state.h[3] = 0xa54ff53a;
	ctx->state.h[4] = 0x510e527f;
	ctx->state.h[5] = 0x9b05688c;
	ctx->state.h[6] = 0x1f83d9ab;
	ctx->state.h[7] = 0x5be0cd19;

	ctx->length = 0;
	ft_memset(ctx->buffer, 0, sizeof(ctx->buffer));
}

void sha256_update(sha256_context_t *ctx, const void *buf, size_t len)
{
	generic_update((void*)ctx, buf, len, sizeof(ctx->buffer), (void*)&sha256_transform);
}

void sha256_transform(sha256_context_t *ctx, const unsigned char block[64])
{
#define xor ^
#define rightshift >>
#define and &
#define not ~

	unsigned w[64] = { 0 };

	ft_memcpy(w, block, sizeof(unsigned) * 16);
	for (unsigned i = 0; i < 16; ++i)
		w[i] = ft_bswap32(w[i]);

	for (unsigned i = 16; i < 64; ++i)
	{
		unsigned s0 = ft_rotr32(w[i - 15], 7) xor ft_rotr32(w[i - 15], 18) xor (w[i - 15] rightshift 3);
		unsigned s1 = ft_rotr32(w[i - 2], 17) xor ft_rotr32(w[i - 2], 19) xor (w[i - 2] rightshift 10);

		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}

	unsigned a = ctx->state.h[0];
	unsigned b = ctx->state.h[1];
	unsigned c = ctx->state.h[2];
	unsigned d = ctx->state.h[3];
	unsigned e = ctx->state.h[4];
	unsigned f = ctx->state.h[5];
	unsigned g = ctx->state.h[6];
	unsigned h = ctx->state.h[7];

	for (unsigned i = 0; i < 64; ++i)
	{
		unsigned S1 = ft_rotr32(e, 6) xor ft_rotr32(e, 11) xor ft_rotr32(e, 25);
		unsigned ch = (e and f) xor ((not e) and g);
		unsigned temp1 = h + S1 + ch + k[i] + w[i];
		unsigned S0 = ft_rotr32(a, 2) xor ft_rotr32(a, 13) xor ft_rotr32(a, 22);
		unsigned maj = (a and b) xor (a and c) xor (b and c);
		unsigned temp2 = S0 + maj;

		h = g;
		g = f;
		f = e;
		e = d + temp1;
		d = c;
		c = b;
		b = a;
		a = temp1 + temp2;
	}

	ctx->state.h[0] += a;
	ctx->state.h[1] += b;
	ctx->state.h[2] += c;
	ctx->state.h[3] += d;
	ctx->state.h[4] += e;
	ctx->state.h[5] += f;
	ctx->state.h[6] += g;
	ctx->state.h[7] += h;
}

void sha256_end(sha256_context_t *ctx, unsigned char digest[32])
{
	sha_end((void*)ctx, (void*)&sha256_update);

	ft_memcpy(digest, &ctx->state, sizeof(ctx->state));

	unsigned *digest4 = (void*)digest;
	for (unsigned i = 0; i < 8; ++i)
		digest4[i] = ft_bswap32(digest4[i]);
}
