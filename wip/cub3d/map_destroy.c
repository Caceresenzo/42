/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:34:39 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/22 15:34:39 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	map_destroy(void *mlx_ptr, t_map **map_ptr)
{
	t_map	*map;

	map = *map_ptr;
	ft_free_and_release((void **)&(map->spr_ordr));
	ft_free_and_release((void **)&(map->spr_dist));
	if (map->objs)
		map_destroy_grid(map);
	image_destroy_null(mlx_ptr, &(map->sprite));
	map_destroy_textures(mlx_ptr, map);
	ft_free_and_release((void **)map_ptr);
}

void
	map_destroy_textures(void *mlx_ptr, t_map *map)
{
	size_t	index;

	index = 0;
	while (index < 4)
	{
		image_destroy_null(mlx_ptr, &(map->wall_texs[index]));
		index++;
	}
}

void
	map_destroy_grid(t_map *map)
{
	t_vec2i			vec;
	t_game_object	*obj;

	vec.y = 0;
	while (vec.y < map->size.h)
	{
		vec.x = 0;
		while (vec.x < map->size.w)
		{
			if ((obj = &(map->objs[vec.y][vec.x])))
				free(obj->data);
			vec.x += 1;
		}
		free(map->objs[vec.y]);
		vec.y += 1;
	}
	ft_free_and_release((void **)&(map->objs));
}
