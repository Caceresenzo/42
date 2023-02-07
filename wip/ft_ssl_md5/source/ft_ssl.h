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

typedef struct
{
	const char *name;
	unsigned context_size;
	unsigned digest_size;
	void (*begin)(void*);
	void (*update)(void*, const void*, unsigned int);
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
void md5_update(md5_context_t *ctx, const void *buf, unsigned int len);
void md5_end(md5_context_t *ctx, unsigned char digest[16]);

void md5_transform(md5_context_t *ctx, const unsigned char block[64]);

unsigned left_rotate(unsigned x, unsigned nbits);

#endif
