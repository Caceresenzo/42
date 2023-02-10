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

#include <stdio.h>

// @formatter:off
static unsigned long k[80] = {
	0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538,
	0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe,
	0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235,
	0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
	0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab,
	0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725,
	0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed,
	0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
	0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218,
	0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53,
	0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373,
	0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
	0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c,
	0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6,
	0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc,
	0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817
};

static unsigned char PADDING[128 + 8] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0,
	/* extra: no 128bit int support yet */
	0, 0, 0, 0, 0, 0, 0, 0,
};
// @formatter:on

void sha512_begin(sha512_context_t *ctx)
{
	ctx->state.h[0] = 0x6a09e667f3bcc908;
	ctx->state.h[1] = 0xbb67ae8584caa73b;
	ctx->state.h[2] = 0x3c6ef372fe94f82b;
	ctx->state.h[3] = 0xa54ff53a5f1d36f1;
	ctx->state.h[4] = 0x510e527fade682d1;
	ctx->state.h[5] = 0x9b05688c2b3e6c1f;
	ctx->state.h[6] = 0x1f83d9abfb41bd6b;
	ctx->state.h[7] = 0x5be0cd19137e2179;

	ctx->length = 0;
	ft_memset(ctx->buffer, 0, sizeof(ctx->buffer));
}

void sha512_update(sha512_context_t *ctx, const void *buf, size_t len)
{
	generic_update((void*)ctx, buf, len, sizeof(ctx->buffer), (void*)&sha512_transform);
}

void sha512_transform(sha512_context_t *ctx, const unsigned char block[128])
{
#define xor ^
#define rightshift >>
#define and &
#define not ~

//	for (unsigned i = 0; i < 128; ++i)
//		printf("%02x ", block[i]);
//	printf("\n");

	unsigned long w[80] = { 0 };

	ft_memcpy(w, block, sizeof(unsigned long) * 16);
	for (unsigned i = 0; i < 16; ++i)
		w[i] = ft_bswap64(w[i]);

	for (unsigned i = 16; i < 80; ++i)
	{
		unsigned long s0 = ft_rotr64(w[i - 15], 1) xor ft_rotr64(w[i - 15], 8) xor (w[i - 15] rightshift 7);
		unsigned long s1 = ft_rotr64(w[i - 2], 19) xor ft_rotr64(w[i - 2], 61) xor (w[i - 2] rightshift 6);

		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}

	unsigned long a = ctx->state.h[0];
	unsigned long b = ctx->state.h[1];
	unsigned long c = ctx->state.h[2];
	unsigned long d = ctx->state.h[3];
	unsigned long e = ctx->state.h[4];
	unsigned long f = ctx->state.h[5];
	unsigned long g = ctx->state.h[6];
	unsigned long h = ctx->state.h[7];

	for (unsigned i = 0; i < 80; ++i)
	{
		unsigned long S1 = ft_rotr64(e, 14) xor ft_rotr64(e, 18) xor ft_rotr64(e, 41);
		unsigned long ch = (e and f) xor ((not e) and g);
		unsigned long temp1 = h + S1 + ch + k[i] + w[i];
		unsigned long S0 = ft_rotr64(a, 28) xor ft_rotr64(a, 34) xor ft_rotr64(a, 39);
		unsigned long maj = (a and b) xor (a and c) xor (b and c);
		unsigned long temp2 = S0 + maj;

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

void sha512_end(sha512_context_t *ctx, unsigned char digest[64])
{
	unsigned long L = ft_bswap64(ctx->length * 8);
	unsigned char bits[8];
	ft_memcpy(bits, &L, sizeof(L));

	unsigned padding_length = 128 - (ctx->length % 128);
//	printf("B padding_length=%u\n", padding_length);
	if (padding_length <= 16)
		padding_length += 128 - 16;
	else
		padding_length -= 16;

//	printf("A padding_length=%u\n", padding_length);

	sha512_update(ctx, PADDING, padding_length + 8);
	sha512_update(ctx, bits, sizeof(bits));

	ft_memcpy(digest, &ctx->state, sizeof(ctx->state));

	unsigned long *digest8 = (void*)digest;
	for (unsigned i = 0; i < 8; ++i)
		digest8[i] = ft_bswap64(digest8[i]);
}
