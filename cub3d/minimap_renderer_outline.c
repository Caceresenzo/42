/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_renderer_outline.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 15:42:57 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/24 15:42:57 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		g_minimap_outline_color = 0x0;

void
	minimap_render_outline(t_image *canvas, t_map *map, t_vec2i offset)
{
	t_vec2i			vec;

	vec.y = 0;
	while (vec.y < map->size.h)
	{
		vec.x = 0;
		while (vec.x < map->size.w)
		{
			if (vec.y == 0 || vec.x == 0 || vec.x == map->size.w - 1
				|| vec.y == map->size.h - 1)
			{
				minimap_render_block(canvas, (t_vec2i) {
					vec.x * MINIMAP_RES - (MINIMAP_RES / 3),
					vec.y * MINIMAP_RES - (MINIMAP_RES / 3)
				}, g_minimap_outline_color, offset);
				minimap_render_block(canvas, (t_vec2i) {
					vec.x * MINIMAP_RES + (MINIMAP_RES / 3),
					vec.y * MINIMAP_RES + (MINIMAP_RES / 3)
				}, g_minimap_outline_color, offset);
			}
			vec.x += 1;
		}
		vec.y += 1;
	}
}
