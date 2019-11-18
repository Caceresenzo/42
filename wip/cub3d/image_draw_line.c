/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_draw_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:55:52 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/18 14:55:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	image_set_pixel(t_image *image, int x, int y, int color)
{
	size_t	offset;
	int		rgb[3];

	offset = (y * image->stride) + (x * image->bpp);
	color_dismentle(color, &(rgb[0]), &(rgb[1]), &(rgb[2]));
	image->pic[offset + 0] = rgb[2];
	image->pic[offset + 1] = rgb[1];
	image->pic[offset + 2] = rgb[0];
	image->pic[offset + 3] = 0;
}

void
	image_draw_vertical_line(t_drawer_line_args args, int x, int y_start,
								int y_end)
{
	int		y;
	size_t	offset;
	int		rgb[3];

	y = y_start;
	offset = (y * args.image->stride) + (x * args.image->bpp);
	color_dismentle(args.color, &(rgb[0]), &(rgb[1]), &(rgb[2]));
	while (y < y_end)
	{
		args.image->pic[offset + 0] = rgb[2];
		args.image->pic[offset + 1] = rgb[1];
		args.image->pic[offset + 2] = rgb[0];
		args.image->pic[offset + 3] = 0;
		offset += args.image->stride;
		y++;
	}
}
