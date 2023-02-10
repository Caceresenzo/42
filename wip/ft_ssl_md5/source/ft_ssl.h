/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 00:54:23 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/07 00:54:23 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H_
# define FT_SSL_H_

# include <stddef.h>
# include <stdbool.h>

typedef struct
{
	bool stdin_;
	bool quiet;
	bool reverse;
	const char *string;
} flags_t;

typedef struct
{
	const char *name;
	unsigned context_size;
	unsigned digest_size;
	void (*begin)(void*);
	void (*update)(void*, const void*, size_t);
	void (*end)(void*, unsigned char*);
} algorithm_t;

typedef struct
{
	unsigned long length;
	unsigned char buffer[64];
	struct
	{
		unsigned a;
		unsigned b;
		unsigned c;
		unsigned d;
	} state;
} md5_context_t;

void md5_begin(md5_context_t *ctx);
void md5_update(md5_context_t *ctx, const void *buf, size_t len);
void md5_transform(md5_context_t *ctx, const unsigned char block[64]);
void md5_end(md5_context_t *ctx, unsigned char digest[16]);

typedef struct
{
	unsigned long length;
	unsigned char buffer[];
} generic_context_t;

void generic_update(generic_context_t *ctx, const void *buf, size_t len, unsigned block_size, void (*transform)(void*, const unsigned char[]));

typedef struct
{
	unsigned long length;
	unsigned char buffer[64];
	struct
	{
		unsigned h[8];
	} state;
} sha256_context_t;

void sha256_begin(sha256_context_t *ctx);
void sha256_update(sha256_context_t *ctx, const void *buf, size_t len);
void sha256_transform(sha256_context_t *ctx, const unsigned char block[64]);
void sha256_end(sha256_context_t *ctx, unsigned char digest[32]);

typedef sha256_context_t sha224_context_t;

void sha224_begin(sha224_context_t *ctx);
void sha224_update(sha224_context_t *ctx, const void *buf, size_t len);
void sha224_end(sha224_context_t *ctx, unsigned char digest[28]);

typedef struct
{
	unsigned long length;
	unsigned char buffer[128];
	struct
	{
		unsigned long h[8];
	} state;
} sha512_context_t;

void sha512_begin(sha512_context_t *ctx);
void sha512_update(sha512_context_t *ctx, const void *buf, size_t len);
void sha512_transform(sha512_context_t *ctx, const unsigned char block[128]);
void sha512_end(sha512_context_t *ctx, unsigned char digest[64]);

typedef sha512_context_t sha384_context_t;

void sha384_begin(sha384_context_t *ctx);
void sha384_update(sha384_context_t *ctx, const void *buf, size_t len);
void sha384_end(sha384_context_t *ctx, unsigned char digest[48]);

int ft_strcmp(const char *s1, const char *s2);
void* ft_memset(void *b, int c, size_t len);
void* ft_memcpy(void *dst, const void *src, size_t n);
size_t ft_strlen(const char *str);
unsigned ft_rotl32(unsigned x, unsigned nbits);
unsigned ft_rotr32(unsigned x, unsigned nbits);
unsigned long ft_rotl64(unsigned long x, unsigned nbits);
unsigned long ft_rotr64(unsigned long x, unsigned nbits);
unsigned ft_bswap32(unsigned x);
unsigned long ft_bswap64(unsigned long x);

#endif
