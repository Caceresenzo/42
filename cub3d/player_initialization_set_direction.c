/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_initialization_set_direction.c              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:57:24 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/20 13:57:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char
	*player_init_set_direction(t_player *player, t_g_obj_data_player *data)
{
	if (data->dir == 'N')
	{
		player->dir = (t_vec2d) { 0, -1 };
		player->plane = (t_vec2d) { -0.66, 0 };
	}
	else if (data->dir == 'S')
	{
		player->dir = (t_vec2d) { 0, 1 };
		player->plane = (t_vec2d) { 0.66, 0 };
	}
	else if (data->dir == 'E')
	{
		player->dir = (t_vec2d) { -1, 0 };
		player->plane = (t_vec2d) { 0, 0.66 };
	}
	else if (data->dir == 'W')
	{
		player->dir = (t_vec2d) { 1, 0 };
		player->plane = (t_vec2d) { 0, -0.66 };
	}
	else
		return (e("What? Unknown rotation value"));
	return (NULL);
}
