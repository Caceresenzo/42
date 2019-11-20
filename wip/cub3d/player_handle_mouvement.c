/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_handle_mouvement.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:37:10 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/18 12:37:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	i_player_handle_move(t_map *map, t_player *player, int sign)
{
	double	x;
	double	y;

	x = (player->dir.x * player->move_speed.value) * sign;
	y = (player->dir.y * player->move_speed.value) * sign;
	if (map_is_empty_at(map, player->pos.x + x, player->pos.y))
		player->pos.x += x;
	if (map_is_empty_at(map, player->pos.x, player->pos.y + y))
		player->pos.y += y;
}

static void
	i_player_handle_rotation(t_player *plyer, int sign, double amount)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	old_dir_x = plyer->dir.x;
	old_plane_x = plyer->plane.x;
	speed = amount * sign;
	plyer->dir.x = plyer->dir.x * cos(speed) - plyer->dir.y * sin(speed);
	plyer->dir.y = old_dir_x * sin(speed) + plyer->dir.y * cos(speed);
	plyer->plane.x = plyer->plane.x * cos(speed) - plyer->plane.y * sin(speed);
	plyer->plane.y = old_plane_x * sin(speed) + plyer->plane.y * cos(speed);
}

int
	player_handle_mouvement(t_map *map, t_player *player)
{
	int		has_moved;

	player->move_speed.value = fps_counter_get_tick() * player->move_speed.base;
	player->rot_speed.value = fps_counter_get_tick() * player->rot_speed.base;
	has_moved = 0;
	if (key_state_get(KEY_ARROW_UP) && (has_moved = 1))
		i_player_handle_move(map, player, 1);
	if (key_state_get(KEY_ARROW_DOWN) && (has_moved = 1))
		i_player_handle_move(map, player, -1);
	if (key_state_get(KEY_ARROW_LEFT) && (has_moved = 1))
		i_player_handle_rotation(player, 1, player->rot_speed.value);
	if (key_state_get(KEY_ARROW_RIGHT) && (has_moved = 1))
		i_player_handle_rotation(player, -1, player->rot_speed.value);
	return (has_moved);
}
