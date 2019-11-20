/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:44:10 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/18 12:44:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_game_object
	*map_get_object_at(t_map *map, int x, int y)
{
	return (&(map->objs[y][x]));
}

int
	map_is_empty_at(t_map *map, int x, int y)
{
	return (map_get_object_type_at(map, x, y) == OBJ_EMPTY);
}

int
	map_get_object_type_at(t_map *map, int x, int y)
{
	return (map_get_object_at(map, x, y)->type);
}
