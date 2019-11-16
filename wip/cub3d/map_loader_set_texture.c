/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader_set_texture.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 18:39:48 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/13 18:39:48 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char
	*map_loader_set_sprite_texture(t_engine *eng, t_map *map, char *path)
{
	t_image	*image;

	image = image_load(eng, path);
	CHECK_PTR_DEF(image, ft_strjoin("Failed to load texture path: ", path));
	map->sprite = image;
	return (NULL);
}

char
	*map_loader_set_wall_texture(t_engine *eng, t_map *map, char *key,
								char *path)
{
	t_image	*image;
	int		side;

	if (path == NULL)
		return (ft_strjoin("No texture path found for config key: ", key));
	side = -1;
	if (ft_strncmp(key, P_TEX_NORTH, 3) == 0)
		side = NORTH;
	else if (ft_strncmp(key, P_TEX_SOUTH, 3) == 0)
		side = SOUTH;
	else if (ft_strncmp(key, P_TEX_WEST, 3) == 0)
		side = WEST;
	else if (ft_strncmp(key, P_TEX_EAST, 3) == 0)
		side = EAST;
	if (side == -1)
		return (ft_strjoin("Unknown config key: ", key));
	image = image_load(eng, path);
	CHECK_PTR_DEF(image, ft_strjoin("Failed to load texture path: ", path));
	map->wall_texs[side] = image;
	return (NULL);
}