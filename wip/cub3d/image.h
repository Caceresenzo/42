/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 10:43:59 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 10:43:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include "minilibx_mms_beta/mlx.h"
# include "libft/libft.h"

typedef struct	s_image
{
	void		*ptr;
	int			*pic;
	int			bpp;
	int			stride;
	int			endian;
	int			width;
	int			height;
	int			line_unit;
}				t_image;

typedef	struct	s_drawer_line_args
{
	t_image		*image;
	int			color;
}				t_drawer_line_args;

t_image			*image_create(void *mlx_ptr, int width, int height);
t_image			*image_load(void *mlx_ptr, char *path);

void			image_clear(t_image *image);

void			image_draw_vertical_line(t_drawer_line_args args, int x,
											int y_start, int y_end);

#endif
