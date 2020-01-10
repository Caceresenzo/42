/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:50:54 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 10:50:54 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include "libft/libft.h"
# include "image.h"
# include "buffer.h"

typedef struct		s_bmp_header
{
	char			*flag;
	int				reserved;
	int				offset;
	int				file_size;
	int				planes;
	int				bit_per_pixel;
	int				compress;
	int				hr;
	int				vr;
	int				colors;
	int				important_color;
}					t_bmp_header;

typedef struct		s_bmp_encoder
{
	char			*buffer;
	int				width;
	int				height;
	int				extra_bytes;
	int				rgb_size;
	int				header_info_size;
	t_bmp_header	header;
	size_t			row_bytes;
	size_t			buffer_row_bytes;
}					t_bmp_encoder;

int					bmp_encode(int fd, t_image *image);
size_t				bmp_encode_write_header(t_bmp_encoder *encoder,
											t_buffer *buffer);
void				bmp_encode_write_image_data(t_bmp_encoder *encoder,
											t_buffer *buffer, size_t pos);

void				bmp_encoder_initialize(t_bmp_encoder *encoder,
											t_image *image);
void				bmp_encoder_initialize_header(t_bmp_encoder *encoder);

#endif
