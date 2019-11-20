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

char
	*player_init_set_position(t_map *map, t_player *player)
{
	size_t			i;
	size_t			j;
	t_game_object	*obj;
	int				found;
	char			*error;

	i = 0;
	found = 0;
	while (i < map->size.h)
	{
		j = 0;
		while (j < map->size.w)
		{
			if ((obj = &(map->objs[i][j]))->type == OBJ_PLAYER)
			{
				if (found)
					return (E("Multiple player"));
				player->pos = (t_vec2d) { j, i };
				if ((error = player_init_set_direction(player, obj->data)))
					return (error);
				found = 1;
				fflush(stdout);
			}
			j++;
		}
		i++;
	}
	if (found)
		return (NULL);
	return (E("No player found"));
}
