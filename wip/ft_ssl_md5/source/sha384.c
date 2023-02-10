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

void sha384_begin(sha384_context_t *ctx)
{
	ctx->state.h[0] = 0xcbbb9d5dc1059ed8;
	ctx->state.h[1] = 0x629a292a367cd507;
	ctx->state.h[2] = 0x9159015a3070dd17;
	ctx->state.h[3] = 0x152fecd8f70e5939;
	ctx->state.h[4] = 0x67332667ffc00b31;
	ctx->state.h[5] = 0x8eb44a8768581511;
	ctx->state.h[6] = 0xdb0c2e0d64f98fa7;
	ctx->state.h[7] = 0x47b5481dbefa4fa4;

	ctx->length = 0;
	ft_memset(ctx->buffer, 0, sizeof(ctx->buffer));
}

void sha384_update(sha384_context_t *ctx, const void *buf, size_t len)
{
	sha512_update((void*)ctx, buf, len);
}

void sha384_end(sha384_context_t *ctx, unsigned char digest[48])
{
	unsigned char digest_512[64];
	sha512_end(ctx, digest_512);

	ft_memcpy(digest, digest_512, 48);
}
