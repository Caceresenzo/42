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

#define TEX_CHECK(tex, word) if (!tex) return (E("No texture for side: "word));
#define COLOR_CHECK(c, word) if (c == -1) return (E("No color for the: "word));

char
	*map_content_check(t_map *map)
{
	TEX_CHECK(map->wall_texs[NORTH], "NORTH");
	TEX_CHECK(map->wall_texs[SOUTH], "SOUTH");
	TEX_CHECK(map->wall_texs[WEST], "WEST");
	TEX_CHECK(map->wall_texs[EAST], "EAST");
	COLOR_CHECK(map->floor_color, "FLOOR");
	COLOR_CHECK(map->roof_color, "ROOF");
	if (map->sprite_count != 0 && map->sprite == NULL)
		return (E("No sprite texture despite having some on the map"));
	if (map->objs == NULL)
		return (E("No object"));
	return (NULL);
}
