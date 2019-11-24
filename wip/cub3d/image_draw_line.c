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

#include "image.h"

void
	image_draw_vertical_line(t_drawer_line_args args, int x, int y_start,
								int y_end)
{
	int		y;
	size_t	offset;

	if (y_start > y_end)
	{
		y = y_end;
		y_end = y_start;
		y_start = y;
	}
	y = y_start;
	offset = y * args.image->line_unit + x;
	while (y < y_end)
	{
		args.image->pic[offset] = args.color;
		offset += args.image->line_unit;
		y++;
	}
}

void
	image_draw_horizontal_line(t_drawer_line_args args, int x_start, int x_end,
								int y)
{
	int		x;
	size_t	offset;

	if (x_start > x_end)
	{
		x = x_end;
		x_end = x_start;
		x_start = x;
	}
	x = x_start;
	offset = y * args.image->line_unit + x;
	while (x < x_end)
	{
		args.image->pic[offset] = args.color;
		offset++;
		x++;
	}
}
