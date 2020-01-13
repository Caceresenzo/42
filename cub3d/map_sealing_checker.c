/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_sealing_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 12:24:15 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/22 12:24:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int
	i_map_sealing_leak_check(t_map *map, int x, int y)
{
	t_game_object	*obj;

	if (x < 0 || y < 0 || x >= map->size.w || y >= map->size.h)
		return (1);
	obj = map_get_object_at(map, x, y);
	if (obj->flooded)
		return (0);
	obj->flooded = 1;
	if (obj->type == OBJ_WALL)
		return (0);
	return (i_map_sealing_leak_check(map, x, y + 1)
			|| i_map_sealing_leak_check(map, x + 1, y)
			|| i_map_sealing_leak_check(map, x - 1, y)
			|| i_map_sealing_leak_check(map, x, y - 1));
}

int
	map_sealing_check(t_map *map, t_vec2i start_pos)
{
	return (!i_map_sealing_leak_check(map, start_pos.x, start_pos.y));
}
