/*
 ============================================================================
 Name        : ft_ssl_md5.c
 Author      : 
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>
#include <limits.h>

typedef struct
{
	struct
	{
		unsigned a;
		unsigned b;
		unsigned c;
		unsigned d;
	} state;
	unsigned long length;
	char buffer[64];
} algorithm_t;

unsigned left_rotate(unsigned x, unsigned nbits);
void md5_transform(algorithm_t *ctx, const unsigned char block[64]);

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

void md5_begin(algorithm_t *ctx)
{
	ctx->state.a = 0x67452301;
	ctx->state.b = 0xefcdab89;
	ctx->state.c = 0x98badcfe;
	ctx->state.d = 0x10325476;

	ctx->length = 0;
	memset(ctx->buffer, 0, sizeof(ctx->buffer));
}

void md5_update(algorithm_t *ctx, const void *buf, unsigned int len)
{
//	printf("\n\nUPDATE len=%u \n", len);

	unsigned buffer_size;
	while (1)
	{
		buffer_size = ctx->length % 64;
//		printf("B buffer_size=%u\n", buffer_size);

//		printf("B content ");
//		for (unsigned i = 0; i < 64; ++i)
//			printf("%02x ", ctx->buffer[i]);
//		printf("\n");

		if (buffer_size + len >= 64)
		{
			unsigned copied = 64 - buffer_size;
//			printf("  copied %u\n", copied);

			memcpy(ctx->buffer + buffer_size, buf, copied);
			md5_transform(ctx, ctx->buffer);

			len -= copied;
			buf += copied;
			ctx->length += copied;
		}
		else
			break;
	}

	memcpy(ctx->buffer + buffer_size, buf, len);
//	printf("  copied len %u\n", len);
	ctx->length += len;
//	printf("A buffer_size=%lu\n", ctx->length % 64);

//	printf("A content ");
//	for (unsigned i = 0; i < 64; ++i)
//		printf("%02x ", ctx->buffer[i]);
//	printf("\n");
}

void md5_end(algorithm_t *ctx, unsigned char digest[16])
{
	unsigned long total_length_bits = ctx->length * 8;
	unsigned char length_bits[8];
	memcpy(length_bits, &total_length_bits, 8);

	unsigned length_mod = ctx->length % 64;
	unsigned padding_length;
	if (length_mod < 56)
		padding_length = 56 - length_mod;
	else
		padding_length = (64 + 56) - length_mod;

//	printf("padding_length=%u\n", padding_length);
	md5_update(ctx, PADDING, padding_length);
	md5_update(ctx, length_bits, 8);

//	printf("\ntransform ");
//	for (unsigned i = 0; i < 64; ++i)
//		printf("%02x ", ctx->buffer[i]);
//	printf("\n");

	memcpy(digest, &ctx->state, sizeof(ctx->state));
}

void test(const char *expected, const char *input)
{
	algorithm_t ctx;
	md5_begin(&ctx);
	md5_update(&ctx, input, strlen(input));

	unsigned char digest[16];
	md5_end(&ctx, digest);

	unsigned char digest_str[32 + 1] = { 0 };
	for (unsigned i = 0; i < 16; ++i)
		sprintf(digest_str + (i * 2), "%02x", digest[i]);

	if (strcmp(digest_str, expected))
	{
		printf("FAIL: `%s`\n", input);
		printf("  expected %s\n", expected);
		printf("       got %s\n", digest_str);
		abort();
	}
	else
		printf("OK: %s `%s`\n", digest_str, input);
}

//int main(int argc, char **argv)
//{
//	test("8b1a9953c4611296a827abf8c47804d7", "Hello");
//	test("9e107d9d372bb6826bd81d3542a419d6", "The quick brown fox jumps over the lazy dog");
//	test("e4d909c290d0fb1ca068ffaddf22cbd0", "The quick brown fox jumps over the lazy dog.");
//	test("aadab38075c43296ee7e12466ebb03e3", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
//
//	test("d41d8cd98f00b204e9800998ecf8427e", "");
//	test("0cc175b9c0f1b6a831c399e269772661", "a");
//	test("900150983cd24fb0d6963f7d28e17f72", "abc");
//	test("f96b697d7cb7938d525a2f31aaf161d0", "message digest");
//	test("c3fcd3d76192e4007dfb496cca67e13b", "abcdefghijklmnopqrstuvwxyz");
//	test("d174ab98d277d9f5a5611c2c9f419d9f", "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");
//	test("57edf4a22be3c955ac49da2e2107b67a", "12345678901234567890123456789012345678901234567890123456789012345678901234567890");
//
//	int fd = open(argv[1], O_RDONLY);
//	if (fd == -1)
//	{
//		perror("open");
//		return (EXIT_FAILURE);
//	}
//
//	algorithm_t ctx;
//	md5_begin(&ctx);
//
//	char buffer[128];
//	ssize_t code;
//
//	while ((code = read(fd, buffer, sizeof(buffer))) == sizeof(buffer))
//		md5_update(&ctx, buffer, code);
//
//	if (code != -1)
//		md5_update(&ctx, buffer, code);
//
//	unsigned char digest[16];
//	md5_end(&ctx, digest);
//
//	for (unsigned i = 0; i < 16; ++i)
//		printf("%02x", digest[i]);
//
//	close(fd);
//	return (EXIT_SUCCESS);
//}

void md5_transform(algorithm_t *ctx, const unsigned char block[64])
{
#define and &
#define or |
#define not ~
#define xor ^
#define mod %

	unsigned int M[16];
	memcpy(M, block, sizeof(M));

	unsigned A = ctx->state.a;
	unsigned B = ctx->state.b;
	unsigned C = ctx->state.c;
	unsigned D = ctx->state.d;

	for (unsigned i = 0; i < 64; ++i)
	{
		unsigned F;
		unsigned g;

		if (0 <= i && i <= 15)
		{
			F = (B and C) or ((not B) and D);
			g = i;
		}
		else if (16 <= i && i <= 31)
		{
			F = (D and B) or ((not D) and C);
			g = (5 * i + 1) mod 16;
		}
		else if (32 <= i && i <= 47)
		{
			F = B xor C xor D;
			g = (3 * i + 5) mod 16;
		}
		else if (48 <= i && i <= 63)
		{
			F = C xor (B or (not D));
			g = (7 * i) mod 16;
		}

		F = F + A + K[i] + M[g];
		A = D;
		D = C;
		C = B;
		B = B + left_rotate(F, s[i]);

//		printf("A=%u B=%u C=%u D=%u\n", A, B, C, D);
	}

	ctx->state.a += A;
	ctx->state.b += B;
	ctx->state.c += C;
	ctx->state.d += D;
}
