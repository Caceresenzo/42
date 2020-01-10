/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_write_uint_32_le.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 11:54:32 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 11:54:32 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

/*
** From:
** https://github.com/feross/buffer/blob/master/index.js#L1571
*/

void
	buffer_fill(t_buffer *buffer, unsigned char value, size_t start, size_t end)
{
	size_t	index;

	index = start;
	while (index < end && index < buffer->length)
	{
		buffer->data[index] = value;
		index++;
	}
}
