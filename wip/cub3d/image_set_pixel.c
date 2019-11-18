/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_set_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:47:52 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/18 17:47:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	image_set_pixel_raw(int rgb[], t_image *image, int x, int y)
{
	size_t	offset;

	offset = (y * image->stride) + (x * image->bpp);
	image->pic[offset + 0] = rgb[2];
	image->pic[offset + 1] = rgb[1];
	image->pic[offset + 2] = rgb[0];
	image->pic[offset + 3] = 0;
}

void
	image_set_pixel(t_image *image, int x, int y, int color)
{
	int		rgb[3];

	color_dismentle(color, &(rgb[0]), &(rgb[1]), &(rgb[2]));
	image_set_pixel_raw(rgb, image, x, y);
}
