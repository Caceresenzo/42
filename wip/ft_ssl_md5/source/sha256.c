/*
 ============================================================================
 Name        : ft_ssl_sha256.c
 Author      : 
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "ft_ssl.h"

// @formatter:off
/* First 32 bits of the fractional parts of the cube roots of the first 64 primes 2..311: */
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

static unsigned char PADDING[64] = {
	0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
// @formatter:on

void sha256_begin(sha256_context_t *ctx)
{
	/* First 32 bits of the fractional parts of the square roots of the first 8 primes 2..19: */
	ctx->state.h[0] = 0x6a09e667;
	ctx->state.h[1] = 0xbb67ae85;
	ctx->state.h[2] = 0x3c6ef372;
	ctx->state.h[3] = 0xa54ff53a;
	ctx->state.h[4] = 0x510e527f;
	ctx->state.h[5] = 0x9b05688c;
	ctx->state.h[6] = 0x1f83d9ab;
	ctx->state.h[7] = 0x5be0cd19;

	ctx->length = 0;
	memset(ctx->buffer, 0, sizeof(ctx->buffer));
}

void sha256_update(sha256_context_t *ctx, const void *buf, size_t len)
{
//	printf("sha256_update len=%lu\n", len);

	unsigned buffer_size;
	while (1)
	{
		buffer_size = ctx->length % 64;

		if (buffer_size + len >= 64)
		{
			unsigned copied = 64 - buffer_size;

			memcpy(ctx->buffer + buffer_size, buf, copied);
			sha256_transform(ctx, ctx->buffer);

//			printf("buffer_size=%u len=%lu copied=%u\n", buffer_size, len, copied);
			len -= copied;
			buf += copied;
			ctx->length += copied;
		}
		else
			break;
	}

//	printf("buffer_size=%u len=%lu\n", buffer_size, len);
	memcpy(ctx->buffer + buffer_size, buf, len);
	ctx->length += len;
}

void dump_bin(const char *name, const void *ptr, size_t len, size_t size, bool space)
{
	(void)name;
	(void)ptr;
	(void)len;
	(void)size;
	(void)space;
	const unsigned char *buffer = ptr;

	printf("--- %s ---\n", name);
	for (size_t index = 0; index < len; index += size)
	{
		if (index % 4 == 0)
		{
			if (index != 0)
				printf("\n");

			printf("%-4ld  ", index / 4);
		}

		for (size_t jndex = size; jndex != 0; --jndex)
		{
			unsigned char byte = buffer[index + jndex - 1];
			for (int mark = 0b10000000; mark != 0; mark >>= 1)
			{
				if (byte & mark)
					printf("1");
				else
					printf("0");
			}

			if (space)
				printf(" ");
		}
	}

	printf("\n");
}

void sha256_transform(sha256_context_t *ctx, const unsigned char block[64])
{
#define xor ^
#define rightshift >>
#define and &
#define not ~

//	unsigned test = (unsigned)0xBC61BD;
//	test = test >> 3;
//	write(1, &test, sizeof(test));
//	exit(0);
//	char test2[] = "Hell";
//	dump_bin("test", &test, sizeof(test), sizeof(test), true);
//	dump_bin("test2", &test2, strlen(test2), true);

//	for (int n = 0; n < 20; ++n)
//	{
//		char name[] = "x0";
//		name[1] += n;
//
//		test >>= 1;
//		dump_bin(name, &test, sizeof(test), sizeof(test), false);
//	}
//
//	exit(0);
//	return;

//	dump_bin("block", block, 64, sizeof(char), true);

	/* create a 64-entry message schedule array w[0..63] of 32-bit words */
	unsigned w[64] = { 0 };

	/* copy chunk into first 16 words w[0..15] of the message schedule array */
	memcpy(w, block, sizeof(unsigned) * 16);
	for (unsigned i = 0; i < 16; ++i)
		w[i] = __builtin_bswap32(w[i]);

	/* Extend the first 16 words into the remaining 48 words w[16..63] of the message schedule array: */
	for (unsigned i = 16; i < 64; ++i)
	{
//		if (i == 16)
//		{
//			unsigned x = w[i - 15];
//			dump_bin("W1", &x, sizeof(x), sizeof(x), false);
//
////			for (int n = 0; n < 20; ++n)
////			{
////				char name[] = "x0";
////				name[1] += n;
////
////				x >>= 1;
////				dump_bin(name, &x, sizeof(x), sizeof(x), false);
////			}
//
//			x = right_rotate(w[i - 15], 7);
//			dump_bin("rr7", &x, sizeof(x), sizeof(x), false);
//
//			x = right_rotate(w[i - 15], 18);
//			dump_bin("rr18", &x, sizeof(x), sizeof(x), false);
//
//			x = (w[i - 15] rightshift 3);
//			dump_bin("rs3", &x, sizeof(x), sizeof(x), false);
//
//			x = right_rotate(w[i - 15], 7) xor right_rotate(w[i - 15], 18) xor (w[i - 15] rightshift 3);
//			dump_bin("s0", &x, sizeof(x), sizeof(x), false);
//
//			x = w[i - 2];
//			dump_bin("W14", &x, sizeof(x), sizeof(x), false);
//
//			x = right_rotate(w[i - 2], 17);
//			dump_bin("rr17", &x, sizeof(x), sizeof(x), false);
//
//			x = right_rotate(w[i - 2], 19);
//			dump_bin("rr19", &x, sizeof(x), sizeof(x), false);
//
//			x = (w[i - 2] rightshift 10);
//			dump_bin("rs10", &x, sizeof(x), sizeof(x), false);
//
//			x = right_rotate(w[i - 2], 17) xor right_rotate(w[i - 2], 19) xor (w[i - 2] rightshift 10);
//			dump_bin("s1", &x, sizeof(x), sizeof(x), false);
//		}
//		return;

		unsigned s0 = right_rotate(w[i - 15], 7) xor right_rotate(w[i - 15], 18) xor (w[i - 15] rightshift 3);
		unsigned s1 = right_rotate(w[i - 2], 17) xor right_rotate(w[i - 2], 19) xor (w[i - 2] rightshift 10);

		w[i] = w[i - 16] + s0 + w[i - 7] + s1;
	}

//	dump_bin("w", w, sizeof(w), sizeof(unsigned), false);
//	dump_bin("initial", &ctx->state.h, sizeof(ctx->state.h), sizeof(unsigned), false);

	/* Initialize working variables to current hash value: */
	unsigned a = ctx->state.h[0];
	unsigned b = ctx->state.h[1];
	unsigned c = ctx->state.h[2];
	unsigned d = ctx->state.h[3];
	unsigned e = ctx->state.h[4];
	unsigned f = ctx->state.h[5];
	unsigned g = ctx->state.h[6];
	unsigned h = ctx->state.h[7];

	/* Compression function main loop: */

	for (unsigned i = 0; i < 64; ++i)
	{
//		printf("------------ i = %u\n", i);
		unsigned S1 = right_rotate(e, 6) xor right_rotate(e, 11) xor right_rotate(e, 25);
		unsigned ch = (e and f) xor ((not e) and g);
		unsigned temp1 = h + S1 + ch + k[i] + w[i];
		unsigned S0 = right_rotate(a, 2) xor right_rotate(a, 13) xor right_rotate(a, 22);
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

//		unsigned buff[] = { a, b, c, d, e, f, g, h };
//		dump_bin("working variables", buff, sizeof(buff), sizeof(unsigned), false);
	}

	/* Add the compressed chunk to the current hash value: */
	ctx->state.h[0] += a;
	ctx->state.h[1] += b;
	ctx->state.h[2] += c;
	ctx->state.h[3] += d;
	ctx->state.h[4] += e;
	ctx->state.h[5] += f;
	ctx->state.h[6] += g;
	ctx->state.h[7] += h;

//	dump_bin("h", &ctx->state.h, sizeof(ctx->state.h), sizeof(unsigned), false);
}

void sha256_end(sha256_context_t *ctx, unsigned char digest[32])
{
	unsigned long L = endian_small_to_big_long(ctx->length * 8);
	unsigned char bits[8];
	memcpy(bits, &L, sizeof(L));

//	unsigned padding_length = 64 - 8 - (ctx->length % 64);
//	if (padding_length == 8)
//		padding_length = 64;
	unsigned padding_length = 64 - (ctx->length % 64);
//	printf("padding_length=%u\n", padding_length);
	if (padding_length <= 8)
		padding_length += 64 - 8;
	else
		padding_length -= 8;
//	printf("padding_length=%u\n", padding_length);

	sha256_update(ctx, PADDING, padding_length);
	sha256_update(ctx, bits, sizeof(bits));

	memcpy(digest, &ctx->state, sizeof(ctx->state));

	unsigned *digest4 = (void*)digest;
	for (unsigned i = 0; i < 8; ++i)
		digest4[i] = __builtin_bswap32(digest4[i]);
}
