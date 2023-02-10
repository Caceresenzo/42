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

#include <stdio.h>

void generic_update(generic_context_t *ctx, const void *buf, size_t len, unsigned block_size, void (*transform)(void*, const unsigned char[]))
{
//	printf("\n\nUPDATE\n");
	unsigned buffer_size;
	while (1)
	{
		buffer_size = ctx->length % block_size;
//		printf("buffer_size=%u\n", buffer_size);

		if (buffer_size + len >= block_size)
		{
			unsigned copied = block_size - buffer_size;
//			printf("transform copied=%u\n", copied);

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
//	printf("ctx->length=%lu\n", ctx->length);
}
