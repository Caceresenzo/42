/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sprite_precomputer_order.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:29:08 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 16:29:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	ray_sprite_precomputer_order(t_player *player, t_map *map)
{
	size_t	index;
	t_vec2d	player_pos;
	t_vec2d	pos;

	index = 0;
	player_pos = player->pos;
	while (index < map->sprite_count)
	{
		pos = map->sprts[index]->pos;
		map->spr_ordr[index] = index;
		map->spr_dist[index] = ((player_pos.x - pos.x) * (player_pos.x - pos.x)
							+ (player_pos.y - pos.y) * (player_pos.y - pos.y));
		index++;
	}
	ft_sort_comp(map->spr_ordr, map->spr_dist, map->sprite_count);
}
