/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer_write_uint_16_le.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 12:09:28 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 12:09:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "buffer.h"

/*
** From:
** https://github.com/feross/buffer/blob/master/index.js#L1343
*/

size_t
	buffer_write_uint_16_le(t_buffer *buffer, unsigned int value, size_t offset)
{
	value = +value;
	offset = ft_lsr(offset, 0);
	buffer->data[offset + 0] = value & 0xFF;
	buffer->data[offset + 1] = ft_lsr(value, 8) & 0xFF;
	return (offset + 2);
}
