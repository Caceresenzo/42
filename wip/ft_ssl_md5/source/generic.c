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

void generic_update(generic_context_t *ctx, const void *buf, size_t len, void (*transform)(void*, const unsigned char[]))
{
	unsigned buffer_size;
	while (1)
	{
		buffer_size = ctx->length % 64;

		if (buffer_size + len >= 64)
		{
			unsigned copied = 64 - buffer_size;

			ft_memcpy(ctx->buffer + buffer_size, buf, copied);
			transform(ctx, ctx->buffer);

			len -= copied;
			buf += copied;
			ctx->length += copied;
		}
		else
			break;
	}

	ft_memcpy(ctx->buffer + buffer_size, buf, len);
	ctx->length += len;
}
