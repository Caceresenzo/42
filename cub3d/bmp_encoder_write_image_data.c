/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_encoder_write_image_data.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 12:33:03 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 12:33:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"
#include "maths.h"

static void
	bmp_encode_write_image_data_fill_extra(t_bmp_encoder *encoder,
											t_buffer *buffer,
											size_t pos, int y)
{
	size_t offset;

	offset = pos + y * encoder->row_bytes + encoder->width * 3;
	buffer_fill(buffer, 0, offset, offset + encoder->extra_bytes);
}

void
	bmp_encode_write_image_data(t_bmp_encoder *encoder, t_buffer *buffer,
								size_t pos)
{
	size_t	index;
	t_vec2i	vec;
	size_t	offset;
	size_t	buffer_offset;

	index = 0;
	vec = (t_vec2i) { 0, 0, };
	while (vec.y < encoder->height)
	{
		vec.x = 0;
		while (vec.x < encoder->width)
		{
			offset = pos + vec.y * encoder->row_bytes + vec.x * 3;
			buffer_offset = encoder->buffer_row_bytes * vec.y + vec.x * 4;
			buffer->data[offset + 0] = encoder->buffer[buffer_offset + 0];
			buffer->data[offset + 1] = encoder->buffer[buffer_offset + 1];
			buffer->data[offset + 2] = encoder->buffer[buffer_offset + 2];
			index += 4;
			vec.x += 1;
		}
		if (encoder->extra_bytes > 0)
			bmp_encode_write_image_data_fill_extra(encoder, buffer, pos, vec.y);
		vec.y += 1;
	}
}
