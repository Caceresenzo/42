/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_initialization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 14:31:59 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/19 14:31:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	player_initialization_set_speed(t_player *player)
{
	player->sprint_mult = 1.5;
	player->move_speed.base = 2.5;
	player->rot_speed.base = 1.5;
}

char
	*player_initialize(t_engine *engine)
{
	char		*error;
	t_player	*player;

	error = NULL;
	player = &(engine->player);
	player_initialization_set_speed(player);
	error = player_init_set_position(engine->map, player);
	return (error);
}
