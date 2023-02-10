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
	struct
	{
		unsigned a;
		unsigned b;
		unsigned c;
		unsigned d;
	} state;
	unsigned long length;
	unsigned char buffer[64];
} md5_context_t;

void md5_begin(md5_context_t *ctx);
void md5_update(md5_context_t *ctx, const void *buf, size_t len);
void md5_transform(md5_context_t *ctx, const unsigned char block[64]);
void md5_end(md5_context_t *ctx, unsigned char digest[16]);

typedef struct
{
	struct
	{
		unsigned h[8];
	} state;
	unsigned long length;
	unsigned char buffer[64];
} sha256_context_t;

void sha256_begin(sha256_context_t *ctx);
void sha256_update(sha256_context_t *ctx, const void *buf, size_t len);
void sha256_transform(sha256_context_t *ctx, const unsigned char block[64]);
void sha256_end(sha256_context_t *ctx, unsigned char digest[32]);

int ft_strcmp(const char *s1, const char *s2);
void* ft_memset(void *b, int c, size_t len);
void* ft_memcpy(void *dst, const void *src, size_t n);
size_t ft_strlen(const char *str);
unsigned ft_left_rotate(unsigned x, unsigned nbits);
unsigned ft_right_rotate(unsigned x, unsigned nbits);
unsigned ft_bswap_uint32(unsigned x);
unsigned long ft_bswap_uint64(unsigned long x);

#endif
