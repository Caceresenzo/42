/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 00:57:49 by ecaceres          #+#    #+#             */
/*   Updated: 2023/02/07 00:57:49 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void uint128_zero(uint128_t *value)
{
	(*value)[0] = 0;
	(*value)[1] = 0;
}

void uint128_add(uint128_t *value, unsigned long add)
{
	(*value)[0] += add;

	if ((*value)[0] < add)
		(*value)[1]++;
}

void generic_update_64(generic_context_64_t *ctx, const void *buf, size_t len, unsigned block_size, void (*transform)(void*, const unsigned char[]))
{
	unsigned buffer_size = ctx->length % block_size;

	if (buffer_size + len >= block_size)
	{
		unsigned copied = block_size - buffer_size;

		ft_memcpy(ctx->buffer + buffer_size, buf, copied);
		transform(ctx, ctx->buffer);

		len -= copied;
		buf += copied;
		ctx->length += copied;

		while (len >= block_size)
		{
			transform(ctx, buf);

			len -= block_size;
			buf += block_size;
			ctx->length += block_size;
		}
	}

	buffer_size = ctx->length % block_size;
	ft_memcpy(ctx->buffer + buffer_size, buf, len);
	ctx->length += len;
}

void generic_update_128(generic_context_128_t *ctx, const void *buf, size_t len, unsigned block_size, void (*transform)(void*, const unsigned char[]))
{
	unsigned buffer_size = ctx->length[0] % block_size;

	if (buffer_size + len >= block_size)
	{
		unsigned copied = block_size - buffer_size;

		ft_memcpy(ctx->buffer + buffer_size, buf, copied);
		transform(ctx, ctx->buffer);

		len -= copied;
		buf += copied;
		uint128_add(&ctx->length, copied);

		while (len >= block_size)
		{
			transform(ctx, buf);

			len -= block_size;
			buf += block_size;
			uint128_add(&ctx->length, block_size);
		}
	}

	buffer_size = ctx->length[0] % block_size;
	ft_memcpy(ctx->buffer + buffer_size, buf, len);
	uint128_add(&ctx->length, len);
}
