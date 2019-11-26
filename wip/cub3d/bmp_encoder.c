/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_encoder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 17:10:41 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/20 17:10:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

int
	bmp_encode(int fd, t_image *image)
{
	t_bmp_encoder	encoder;
	t_buffer		*buffer;
	size_t			pos;

	bmp_encoder_initialize(&encoder, image);
	bmp_encoder_initialize_header(&encoder);
	buffer = buffer_create(encoder.header.offset + encoder.rgb_size);
	if (!buffer)
		return (0);
	pos = bmp_encode_write_header(&encoder, buffer);
	bmp_encode_write_image_data(&encoder, buffer, pos);
	write(fd, buffer->data, buffer->length);
	buffer_destroy(&buffer);
	return (1);
}
