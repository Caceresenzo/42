/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_encoder_initializer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:57:21 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 10:57:21 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bmp.h"

void
	bmp_encoder_initialize(t_bmp_encoder *encoder, t_image *image)
{
	encoder->buffer = (char *)image->pic;
	encoder->width = image->width;
	encoder->height = image->height;
	encoder->extra_bytes = encoder->width % 4;
	encoder->rgb_size = encoder->height *
							(3 * encoder->width + encoder->extra_bytes);
	encoder->header_info_size = 40;
	encoder->row_bytes = 3 * encoder->width + encoder->extra_bytes;
	encoder->buffer_row_bytes = image->stride;
}

void
	bmp_encoder_initialize_header(t_bmp_encoder *encoder)
{
	t_bmp_header	*header;

	header = &(encoder->header);
	header->flag = "BM";
	header->reserved = 0;
	header->offset = 54;
	header->file_size = encoder->rgb_size + header->offset;
	header->planes = 1;
	header->bit_per_pixel = 24;
	header->compress = 0;
	header->hr = 0;
	header->vr = 0;
	header->colors = 0;
	header->important_color = 0;
}
