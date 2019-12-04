/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_content_checker.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 12:46:41 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/23 12:46:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char
	*map_content_check(t_map *map)
{
	if (!map->wall_texs[0])
		return (e("No texture for side: NORTH"));
	if (!map->wall_texs[1])
		return (e("No texture for side: SOUTH"));
	if (!map->wall_texs[2])
		return (e("No texture for side: WEST"));
	if (!map->wall_texs[3])
		return (e("No texture for side: EAST"));
	if (map->floor_color == -1)
		return (e("No color for the: FLOOR"));
	if (map->roof_color == -1)
		return (e("No color for the: ROOF"));
	if (map->sprite_count != 0 && map->sprite == NULL)
		return (e("No sprite texture despite having some on the map"));
	if (map->objs == NULL)
		return (e("No object"));
	return (NULL);
}
