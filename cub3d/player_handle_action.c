/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_handle_action.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 12:37:10 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/18 12:37:10 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	player_handle_action(t_map *map, t_player *player)
{
	int		has_changed;

	ft_fake_use(&player);
	has_changed = 0;
	if (map->render_minimap != key_state_get(KEY_MINIMAP) && (has_changed = 1))
		map->render_minimap = key_state_get(KEY_MINIMAP);
	return (has_changed);
}
