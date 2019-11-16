/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_loader_set_grid.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:30:25 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/13 19:30:25 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char
	*map_loader_grid_bind_object(t_game_object *current, char *str)
{
	int		type;
	int		dir;
	void	*data;

	type = -1;
	data = NULL;
	if (ft_strncmp(str, "0", 2) == 0)
		type = OBJ_EMPTY;
	else if (ft_strncmp(str, "1", 2) == 0)
		type = OBJ_WALL;
	else if (ft_strncmp(str, "2", 2) == 0)
		type = OBJ_OBJ;
	else if (ft_strlen(str) == 1 && (dir = ft_isinstr(str[0], "NSEW")) != -1)
	{
		type = OBJ_PLAYER;
		data = malloc(sizeof(t_g_obj_data_player));
		CHECK_PTR_DEF(data, E("Failed to malloc() [bind object]"));
		((t_g_obj_data_player *)data)->dir = dir;
	}
	else
		return (ft_strjoin("Unknown game object type: ", str));
	current->type = type;
	current->data = data;
	return (NULL);
}

char
	*map_loader_grid_create_line(t_game_object **grid, t_map *map, char **split)
{
	t_game_object	*objects;
	size_t			index;
	char			*error;

	error = NULL;
	objects = malloc(map->size.w * sizeof(t_game_object));
	CHECK_PTR_DEF(objects, E("Failed to malloc() [create line]"));
	index = 0;
	while (index < map->size.w)
	{
		error = map_loader_grid_bind_object(&(objects[index]), split[index]);
		if (error != NULL)
			break ;
		index++;
	}
	if (error != NULL)
	{
		free(objects);
		objects = NULL;
	}
	*grid = objects;
	return (error);
}

char
	*map_loader_parse_grid(t_engine *eng, t_map *map, char **split)
{
	size_t			length;
	t_game_object	**old;
	t_game_object	*new;
	char			*error;

	error = NULL;
	length = ft_split_length(split);
	if (length != map->size.w && map->size.w != 0)
		return (ft_strdup("Map width not constant"));
	map->size.w = length;
	old = map->objs;
	CHECK_PTR_DEF(map->objs = malloc((map->size.h + 1) *
			sizeof(t_game_object *)), E("Failed to malloc() [parse grid]"));
	ft_memcpy(map->objs, old, map->size.h * sizeof(t_game_object *));
	error = map_loader_grid_create_line(&new, map, split);
	map->objs[map->size.h] = new;
	if (old != NULL)
		free(old);
	if (error != NULL)
	{
		free(map->objs);
		map->objs = NULL;
	}
	map->size.h++;
	return (error);
}
