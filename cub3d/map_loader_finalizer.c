/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader_finalizer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:15:52 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 14:15:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static size_t
	i_map_finalizer_count(t_map *map, int type)
{
	t_vec2i	vec;
	size_t	count;

	vec = (t_vec2i) { 0, 0 };
	count = 0;
	while (vec.y < map->size.h)
	{
		vec.x = 0;
		while (vec.x < map->size.w)
		{
			count += map_get_object_type_at(map, vec.x, vec.y) == type;
			vec.x += 1;
		}
		vec.y += 1;
	}
	return (count);
}

static t_map
	*map_finalizer_store_sprites(t_map *map, size_t count)
{
	size_t	index;
	t_vec2i	vec;

	index = 0;
	if (!(map->sprts = malloc((count + 1) * sizeof(t_game_object *))))
		return (NULL);
	vec = (t_vec2i) { 0, 0 };
	while (vec.y < map->size.h)
	{
		vec.x = 0;
		while (vec.x < map->size.w)
		{
			if (map_get_object_type_at(map, vec.x, vec.y) == OBJ_SPRITE)
			{
				map->sprts[index] = map_get_object_at(map, vec.x, vec.y);
				map->sprts[index]->pos.x += 0.5;
				map->sprts[index]->pos.y += 0.5;
				map->sprite_count = ++index;
			}
			vec.x += 1;
		}
		vec.y += 1;
	}
	map->sprts[map->sprite_count] = NULL;
	return (map);
}

t_map
	*map_finalize(t_map *map)
{
	size_t	count;
	char	*error;

	if ((count = i_map_finalizer_count(map, OBJ_SPRITE)))
	{
		map = map_finalizer_store_sprites(map, count);
		if (!(map->spr_ordr = ft_calloc(count, sizeof(int)))
			|| !(map->spr_dist = ft_calloc(count, sizeof(double))))
			return (NULL);
	}
	if ((error = map_content_check(map)))
		engine_error(error);
	return (map);
}
