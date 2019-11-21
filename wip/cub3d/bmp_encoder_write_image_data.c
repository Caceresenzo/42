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

/*
** if (encoder.extra_bytes > 0)
** {
** 		size_t fillOffset = pos + y * row_bytes + encoder.width * 3;
** 		buffer_fill(buffer, 0, fillOffset, fillOffset + encoder.extra_bytes);
** }
*/

void
	bmp_encode_write_image_data(t_bmp_encoder *encoder, t_buffer *buffer,
								size_t pos)
{
	size_t	index;
	size_t	row_bytes;
	t_vec2i	vec;
	size_t	offset;

	index = 0;
	row_bytes = 3 * encoder->width + encoder->extra_bytes;
	vec = (t_vec2i) { 0, 0, };
	while (vec.y < encoder->height)
	{
		vec.x = 0;
		while (vec.x < encoder->width)
		{
			offset = pos + vec.y * row_bytes + vec.x * 3;
			buffer->data[offset + 0] = encoder->buffer[index + 0];
			buffer->data[offset + 1] = encoder->buffer[index + 1];
			buffer->data[offset + 2] = encoder->buffer[index + 2];
			index += 4;
			vec.x += 1;
		}
		vec.y += 1;
	}
}
