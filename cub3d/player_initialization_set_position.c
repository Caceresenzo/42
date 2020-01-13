/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_initialization_set_position.c               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:56:53 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/20 13:56:53 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char
	*i_player_init_set_position_check(t_map *map, t_player *player,
										t_vec2i *vec, int *found)
{
	t_game_object	*obj;
	char			*error;

	if ((obj = &(map->objs[vec->y][vec->x]))->type == OBJ_PLAYER)
	{
		if (*found)
			return (e("Multiple player"));
		player->pos = (t_vec2d) { vec->x + 0.5, vec->y + 0.5 };
		if ((error = player_init_set_direction(player, obj->data)))
			return (error);
		*found = 1;
	}
	return (NULL);
}

char
	*player_init_set_position(t_map *map, t_player *player)
{
	t_vec2i			vec;
	int				found;
	char			*error;

	vec.y = 0;
	found = 0;
	while (vec.y < map->size.h)
	{
		vec.x = 0;
		while (vec.x < map->size.w)
		{
			error = i_player_init_set_position_check(map, player, &vec, &found);
			if (error)
				return (error);
			vec.x += 1;
		}
		vec.y += 1;
	}
	if (found)
		return (NULL);
	return (e("No player found"));
}
