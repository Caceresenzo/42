/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 00:57:49 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/07 00:57:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "ft_ssl.h"

void sha224_begin(sha224_context_t *ctx)
{
	ctx->state.h[0] = 0xc1059ed8;
	ctx->state.h[1] = 0x367cd507;
	ctx->state.h[2] = 0x3070dd17;
	ctx->state.h[3] = 0xf70e5939;
	ctx->state.h[4] = 0xffc00b31;
	ctx->state.h[5] = 0x68581511;
	ctx->state.h[6] = 0x64f98fa7;
	ctx->state.h[7] = 0xbefa4fa4;

	ctx->length = 0;
	ft_memset(ctx->buffer, 0, sizeof(ctx->buffer));
}

void sha224_update(sha224_context_t *ctx, const void *buf, size_t len)
{
	generic_update((void*)ctx, buf, len, sizeof(ctx->buffer), (void*)&sha256_transform);
}

void sha224_end(sha224_context_t *ctx, unsigned char digest[28])
{
	unsigned char digest_32[32];
	sha256_end((void*)ctx, digest_32);

	ft_memcpy(digest, digest_32, 28);
}
