/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_encoder_write_header.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 12:29:38 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 12:29:38 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

/*
** From:
** https://github.com/shaozilee/bmp-js/blob/master/lib/encoder.js
*/

size_t
	bmp_encode_write_header(t_bmp_encoder *encoder, t_buffer *buffer)
{
	size_t	pos;

	pos = 0;
	pos = buffer_write_ascii(buffer, encoder->header.flag, pos, 2);
	pos = buffer_write_uint_32_le(buffer, encoder->header.file_size, pos);
	pos = buffer_write_uint_32_le(buffer, encoder->header.reserved, pos);
	pos = buffer_write_uint_32_le(buffer, encoder->header.offset, pos);
	pos = buffer_write_uint_32_le(buffer, encoder->header_info_size, pos);
	pos = buffer_write_uint_32_le(buffer, encoder->width, pos);
	pos = buffer_write_int_32_le(buffer, -encoder->height, pos);
	pos = buffer_write_uint_16_le(buffer, encoder->header.planes, pos);
	pos = buffer_write_uint_16_le(buffer, encoder->header.bit_per_pixel, pos);
	pos = buffer_write_uint_32_le(buffer, encoder->header.compress, pos);
	pos = buffer_write_uint_32_le(buffer, encoder->rgb_size, pos);
	pos = buffer_write_uint_32_le(buffer, encoder->header.hr, pos);
	pos = buffer_write_uint_32_le(buffer, encoder->header.vr, pos);
	pos = buffer_write_uint_32_le(buffer, encoder->header.colors, pos);
	pos = buffer_write_uint_32_le(buffer, encoder->header.important_color, pos);
	return (pos);
}
