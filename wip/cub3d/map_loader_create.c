/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 12:13:12 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/25 12:13:12 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map
	*map_create(char *file)
{
	t_map	*map;

	if (!(map = malloc(sizeof(t_map))))
		return (NULL);
	map->file = file;
	map->objs = NULL;
	map->roof_color = -1;
	map->floor_color = -1;
	map->wall_texs[NORTH] = NULL;
	map->wall_texs[SOUTH] = NULL;
	map->wall_texs[WEST] = NULL;
	map->wall_texs[EAST] = NULL;
	map->sprite = NULL;
	map->size.w = 0;
	map->size.h = 0;
	map->sprts = NULL;
	map->spr_ordr = NULL;
	map->spr_dist = NULL;
	map->sprite_count = 0;
	map->render_minimap = 0;
	return (map);
}
