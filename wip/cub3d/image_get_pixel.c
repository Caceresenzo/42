/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_get_pixel.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 17:48:14 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/18 17:48:14 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	image_get_pixel_raw(int rgb[], t_image *image, int x, int y)
{
	size_t	offset;

	offset = (y * image->stride) + (x * image->bpp);
	rgb[2] = image->pic[offset + 0];
	rgb[1] = image->pic[offset + 1];
	rgb[0] = image->pic[offset + 2];
}

int
	image_get_pixel(t_image *image, int x, int y)
{
	int		rgb[3];

	image_get_pixel_raw(rgb, image, x, y);
	return (color_assemble(rgb[0], rgb[1], rgb[2]));
}
