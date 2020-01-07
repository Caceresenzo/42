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

/*
** Note:
** ft_strjoin_free: policy #2 --> FT_STRJOIN_FREE_SECOND
*/

char
	*map_loader_grid_bind_object(t_map *map, size_t index,
								t_game_object *current, char c)
{
	int		type;

	type = -1;
	if (c == '0')
		type = OBJ_EMPTY;
	else if (c == '1')
		type = OBJ_WALL;
	else if (c == '2')
		type = OBJ_SPRITE;
	else if (ft_isinstr(c, "NSEW") != -1)
	{
		type = OBJ_PLAYER;
		current->data = malloc(sizeof(t_g_obj_data_player));
		if (!current->data)
			return (emalloc("bind object"));
		((t_g_obj_data_player *)current->data)->dir = c;
	}
	else
		return (ft_strjoin_free("Unknown game object: ", ft_chrtostr(c), 2));
	current->type = type;
	current->pos = (t_vec2d) { 1.0 * index, 1.0 * map->size.h };
	current->flooded = 0;
	return (NULL);
}

char
	*map_loader_grid_create_line(t_game_object **grid, t_map *map, char *line)
{
	t_game_object	*objects;
	int				index;
	char			*error;

	error = NULL;
	objects = ft_calloc(map->size.w, sizeof(t_game_object));
	if (!objects)
		return (emalloc("create line"));
	index = 0;
	while (index < map->size.w)
	{
		error = map_loader_grid_bind_object(map, index, &(objects[index]),
											line[index]);
		if (error != NULL)
			break ;
		index++;
	}
	*grid = objects;
	return (error);
}

char
	*map_loader_parse_grid(t_engine *eng, t_map *map, char *line)
{
	int				length;
	t_game_object	**old;
	t_game_object	*new;
	char			*error;

	ft_fake_use(&eng);
	if (!(length = ft_strlen(line)))
		return (NULL);
	if (length != map->size.w && map->size.w != 0)
		return (e("Map width not constant"));
	map->size.w = length;
	old = map->objs;
	if (!(map->objs = malloc((map->size.h + 1) * sizeof(t_game_object *))))
		return (emalloc("parse grid"));
	ft_memcpy(map->objs, old, map->size.h * sizeof(t_game_object *));
	error = map_loader_grid_create_line(&new, map, line);
	map->objs[map->size.h] = new;
	if (old != NULL)
		free(old);
	map->size.h++;
	return (error);
}
