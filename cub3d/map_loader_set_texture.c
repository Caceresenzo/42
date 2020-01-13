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
	char	*trim;

	if (path == NULL)
		return (e("No texture path found for the sprite"));
	if (map->sprite != NULL)
		return (e("Already assigned texure: SPRITE"));
	trim = ft_strtrim(path, " ");
	trim = trim == NULL ? path : trim;
	image = image_load(eng->ctx.mlx, trim);
	if (!image)
		return (ft_strjoin("Failed to load texture path: ", trim));
	map->sprite = image;
	if (trim != path)
		free(trim);
	return (NULL);
}

char
	*map_loader_set_wall_texture(t_engine *eng, t_map *map, char *key,
								char *path)
{
	t_image	*image;
	char	*trim;
	int		side;

	if (path == NULL)
		return (ft_strjoin("No texture path found for config key: ", key));
	trim = ft_strtrim(path, " ");
	trim = trim == NULL ? path : trim;
	side = -1;
	side = (side == -1 && ft_strncmp(key, P_TEX_NORTH, 3) == 0) ? NORTH : side;
	side = (side == -1 && ft_strncmp(key, P_TEX_SOUTH, 3) == 0) ? SOUTH : side;
	side = (side == -1 && ft_strncmp(key, P_TEX_WEST, 3) == 0) ? WEST : side;
	side = (side == -1 && ft_strncmp(key, P_TEX_EAST, 3) == 0) ? EAST : side;
	if (side == -1)
		return (ft_strjoin("Unknown config key: ", key));
	if (map->wall_texs[side] != NULL)
		return (ft_strjoin("Already assigned texure: ", map_side_to_str(side)));
	if (!(image = image_load(eng->ctx.mlx, trim)))
		return (ft_strjoin("Failed to load texture path: ", trim));
	map->wall_texs[side] = image;
	if (trim != path)
		free(trim);
	return (NULL);
}
