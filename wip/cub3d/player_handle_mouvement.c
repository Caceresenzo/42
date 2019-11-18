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

void
	i_player_handle_collision(t_map *map, t_player *p, int sign)
{
	double	x;
	double	y;

	x = (p->dir.x * p->move_speed) * sign;
	y = (p->dir.y * p->move_speed) * sign;
	if (map_is_empty_at(map, p->pos.x + x, p->pos.y))
		p->pos.x += x;
	if (map_is_empty_at(map, p->pos.x, p->pos.y + y))
		p->pos.y += y;
}

void
	i_player_handle_rotation(t_map *map, t_player *p, int sign)
{
	double	old_dir_x;
	double	old_plane_x;
	double	speed;

	old_dir_x = p->dir.x;
	old_plane_x = p->plane.x;
	speed = p->rot_speed * sign;
	p->dir.x = p->dir.x * cos(speed) - p->dir.y * sin(speed);
	p->dir.y = old_dir_x * sin(speed) + p->dir.y * cos(speed);
	p->plane.x = p->plane.x * cos(speed) - p->plane.y * sin(speed);
	p->plane.y = old_plane_x * sin(speed) + p->plane.y * cos(speed);
}

int
	player_handle_mouvement(t_map *map, t_player *player)
{
	int		has_moved;

	has_moved = 0;
	if (key_state_get(KEY_ARROW_UP) && (has_moved = 1))
		i_player_handle_collision(map, player, 1);
	if (key_state_get(KEY_ARROW_DOWN) && (has_moved = 1))
		i_player_handle_collision(map, player, -1);
	if (key_state_get(KEY_ARROW_LEFT) && (has_moved = 1))
		i_player_handle_rotation(map, player, 1);
	if (key_state_get(KEY_ARROW_RIGHT) && (has_moved = 1))
		i_player_handle_rotation(map, player, -1);
	return (has_moved);
}
