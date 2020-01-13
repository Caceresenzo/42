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

#define MODE_FORWARD_BACKWARD 0
#define MODE_LEFT_RIGHT 1

/*
** For left or right movement:
**		x = dir.x * cos(PI / 2) - dir.y * sin(PI / 2)
**		y = dir.x * sin(PI / 2) + dir.y * cos(PI / 2)
**
** But:
**		cos(PI / 2) = 0
**		sin(PI / 2) = 1
**
** So:
**		x = dir.x * 0 - dir.y * 1
**		y = dir.x * 1 + dir.y * 0
**
** Finally:
**		x = -dir.y
**		y = dir.x
**
** Or:
** 		You can just use the already computed "plane" variable.
*/

static void
	i_player_handle_move(t_map *map, t_player *player, int sign, int mode)
{
	double	x;
	double	y;

	if (mode == MODE_FORWARD_BACKWARD)
	{
		x = player->dir.x;
		y = player->dir.y;
	}
	else if (mode == MODE_LEFT_RIGHT)
	{
		x = -player->plane.x;
		y = -player->plane.y;
	}
	else
		return ;
	x = (x * player->move_speed.value) * sign;
	y = (y * player->move_speed.value) * sign;
	if (!map_is_solid_at(map, player->pos.x + x, player->pos.y))
		player->pos.x += x;
	if (!map_is_solid_at(map, player->pos.x, player->pos.y + y))
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

static void
	i_player_handle_mouse_rotation(t_player *player)
{
	int		off;
	t_vec2i	current;

	current = mouse_pos_current_get();
	off = mouse_pos_last_click_get().x - current.x;
	off = ft_max(-1, ft_min(off, 1)) * MOUSE_SENSIBILITY;
	if (off != 0)
		mouse_pos_update_last_to_current();
	i_player_handle_rotation(player, off, player->rot_speed.value);
}

int
	player_handle_mouvement(t_map *map, t_player *player)
{
	int		has_moved;

	player->move_speed.value = fps_counter_get_tick() * player->move_speed.base;
	player->rot_speed.value = fps_counter_get_tick() * player->rot_speed.base;
	has_moved = 0;
	if (key_state_get(KEY_SHIFT) && BONUS)
		player->move_speed.value *= player->sprint_mult;
	if (key_state_get2(KEY_FORWARD, KEY_FORWARD2) && (has_moved = 1))
		i_player_handle_move(map, player, 1, MODE_FORWARD_BACKWARD);
	if (key_state_get(KEY_BACKWARD) && (has_moved = 1))
		i_player_handle_move(map, player, -1, MODE_FORWARD_BACKWARD);
	if (key_state_get2(KEY_LEFT, KEY_LEFT2) && (has_moved = 1))
		i_player_handle_move(map, player, 1, MODE_LEFT_RIGHT);
	if (key_state_get(KEY_RIGHT) && (has_moved = 1))
		i_player_handle_move(map, player, -1, MODE_LEFT_RIGHT);
	if (mouse_button_state_get(MOUSE_BUTTON_HOOK) && BONUS && (has_moved = 1))
		i_player_handle_mouse_rotation(player);
	else
	{
		if (key_state_get(KEY_ROTATION_LEFT) && (has_moved = 1))
			i_player_handle_rotation(player, 1, player->rot_speed.value);
		if (key_state_get(KEY_ROTATION_RIGHT) && (has_moved = 1))
			i_player_handle_rotation(player, -1, player->rot_speed.value);
	}
	return (has_moved);
}
