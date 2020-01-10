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

static char
	arg_cmp(char *key, const char *arg, int max)
{
	return ((ft_strncmp(key, arg, max) == 0));
}

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
	else if (arg_cmp(key, P_RESOLUTION, 2))
		r = (map_loader_set_resolution(key, split + 1, eng));
	else if (arg_cmp(key, P_SPRITE, 2))
		r = (map_loader_set_sprite_texture(eng, map, path));
	else if (arg_cmp(key, P_FLOOR_COLOR, 2))
		r = (map_loader_set_color(key, split[1], &map->floor_color, "FLOOR"));
	else if (arg_cmp(key, P_ROOF_COLOR, 2))
		r = (map_loader_set_color(key, split[1], &map->roof_color, "ROOF"));
	else
		r = (map_loader_set_wall_texture(eng, map, key, path));
	return (r);
}

static char
	*i_map_loader_parse_line(t_engine *eng, t_map *map, char *line, int *fully)
{
	char	**split;
	char	*key;
	char	*error;

	if (!(split = ft_split(line, ' ')))
		return (emalloc("line parser"));
	error = NULL;
	key = split[0];
	if (*fully == 2 && key != NULL)
		return (e("More content after map data") + (int)ft_split_free(&split));
	if (key == NULL)
	{
		*fully = *fully == 1 ? 2 : *fully;
		return (0 + ft_split_free(&split));
	}
	if (map->objs || (!map->objs && ft_isinstr(split[0][0], "012") != -1))
	{
		key = ft_strjoin_split(split);
		error = map_loader_parse_grid(eng, map, key);
		free(key + ((*fully = 1) - 1));
	}
	else
		error = i_map_loader_interpret_key(eng, map, line, split);
	ft_split_free(&split);
	return (error);
}

t_map
	*i_map_load_from_fd(t_engine *eng, int fd)
{
	int		returned;
	int		fully;
	char	*line;
	char	*error;

	eng->map->objs = NULL;
	fully = 0;
	while (1)
	{
		returned = get_next_line(fd, &line);
		error = i_map_loader_parse_line(eng, eng->map, line, &fully);
		free(line);
		if (error != NULL)
			engine_error(error);
		if (!returned)
			break ;
	}
	return (map_finalize(eng->map));
}

t_map
	*map_load(t_engine *eng, char *path)
{
	int		fd;
	t_map	*map;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (engine_error_raison(ft_strjoin("Failed to read file: ", path)));
	if (!map_loader_check_file_extension(path))
	{
		close(fd);
		return (engine_error(ft_strjoin("Invalid file extension, ",
						"only \""CUB3D_FILE_EXTENSION"\" is accepted")));
	}
	if (!(eng->map = map_create(path)))
		return (NULL);
	map = i_map_load_from_fd(eng, fd);
	close(fd);
	return (map);
}
