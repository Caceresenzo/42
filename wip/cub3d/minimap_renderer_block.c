/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_renderer_block.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 15:41:54 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/24 15:41:54 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	minimap_render_block(t_image *canvas, t_vec2i pos, int color,
							t_vec2i offset)
{
	t_vec2i			vec;
	t_vec2i			abs_pos;

	vec.y = 0;
	while (vec.y < MINIMAP_RES)
	{
		vec.x = 0;
		while (vec.x < MINIMAP_RES)
		{
			abs_pos.x = vec.x + offset.x + pos.x;
			abs_pos.y = vec.y + offset.y + pos.y;
			image_pixel_set(canvas, abs_pos.x, abs_pos.y, color);
			vec.x += 1;
		}
		vec.y += 1;
	}
}
