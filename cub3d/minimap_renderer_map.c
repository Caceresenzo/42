/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_renderer_map.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 15:43:56 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/24 15:43:56 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		g_minimap_color[] = {
	0x808080,
	0xFF0000,
	0x00FF00,
	0x0000FF,
};

void
	minimap_render_map(t_image *canvas, t_map *map, t_vec2i offset)
{
	t_vec2i			vec;
	t_game_object	*obj;

	vec.y = 0;
	while (vec.y < map->size.h)
	{
		vec.x = 0;
		while (vec.x < map->size.w)
		{
			obj = map_get_object_at(map, vec.x, vec.y);
			minimap_render_block(canvas, (t_vec2i) {
				vec.x * MINIMAP_RES,
				vec.y * MINIMAP_RES
			}, g_minimap_color[obj->type], offset);
			vec.x += 1;
		}
		vec.y += 1;
	}
}
