/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 14:23:28 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/13 14:23:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#define ARG_CMP(arg, max) (ft_strncmp(key, arg, max) == 0)

static char
	*i_map_loader_interpret_key(t_engine *eng, t_map *map, char *line,
								char **split)
{
	char	*key;
	char	*path;
	char	*r;

	key = split[0];
	path = ft_strchr(line, ' ') + 1;
	r = NULL;
	if (split[1] == NULL)
		r = (ft_strjoin("No argument found for config key: ", key));
	else if (ft_strncmp(key, P_RESOLUTION, 2) == 0)
		r = (map_loader_set_resolution(key, split + 1, eng));
	else if (ARG_CMP(P_SPRITE, 2))
		r = (map_loader_set_sprite_texture(eng, map, path));
	else if (ARG_CMP(P_FLOOR_COLOR, 2))
		r = (map_loader_set_color(key, split[1], &map->floor_color));
	else if (ARG_CMP(P_ROOF_COLOR, 2))
		r = (map_loader_set_color(key, split[1], &map->roof_color));
	else
		r = (map_loader_set_wall_texture(eng, map, key, path));
	return (r);
}

static char
	*i_map_loader_parse_line(t_engine *eng, t_map *map, char *line)
{
	char	**split;
	char	*key;
	char	*r;

	CHECK_PTR_DEF(split = ft_split(line, ' '), ft_strdup("Failed to malloc()"));
	r = NULL;
	if (ft_strlen(key = split[0]) != 0)
	{
		if (map->objs || (!map->objs && split[0][0] == '1'))
			r = map_loader_parse_grid(eng, map, split);
		else
			r = i_map_loader_interpret_key(eng, map, line, split);
	}
	ft_split_free(&split);
	return (r);
}

t_map
	*map_create(char *file)
{
	t_map	*map;

	CHECK_MALLOC(map, sizeof(t_map));
	map->file = file;
	map->objs = NULL;
	map->resolution.x = 0;
	map->resolution.y = 0;
	map->roof_color = 0x000000;
	map->floor_color = 0x000000;
	map->wall_texs[NORTH] = NULL;
	map->wall_texs[SOUTH] = NULL;
	map->wall_texs[WEST] = NULL;
	map->wall_texs[EAST] = NULL;
	map->size.w = 0;
	map->size.h = 0;
	map->sprts = NULL;
	return (map);
}

t_map
	*map_load(t_engine *eng, char *path)
{
	int		fd;
	int		returned;
	char	*line;
	char	*error;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (engine_handle_error(ft_strjoin("Failed to read file: ", path)));
	CHECK_PTR(eng->map = map_create(path));
	eng->map->objs = NULL;
	while (1)
	{
		returned = get_next_line(fd, &line);
		error = i_map_loader_parse_line(eng, eng->map, line);
		free(line);
		if (error != NULL)
			engine_handle_error(error);
		if (!returned)
			break ;
	}
	return (map_finalize(eng->map));
}
