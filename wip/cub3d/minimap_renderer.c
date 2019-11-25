/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_renderer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 14:37:01 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/24 14:37:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	minimap_render(t_image *canvas, t_player *player, t_map *map)
{
	t_vec2i			offset;

	offset = (t_vec2i) { (map->size.w + 1) * MINIMAP_RES, MINIMAP_RES };
	offset.x = canvas->width - offset.x;
	minimap_render_outline(canvas, map, offset);
	minimap_render_map(canvas, map, offset);
	minimap_render_player(canvas, player, offset);
}
