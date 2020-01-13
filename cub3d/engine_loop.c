/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:54:24 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/12 15:54:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	engine_loop(t_engine *engine)
{
	int		dirty[2];

	dirty[0] = player_handle_action(engine->map, &(engine->player));
	dirty[1] = player_handle_mouvement(engine->map, &(engine->player));
	engine->dirty = engine->dirty || dirty[0] || dirty[1];
	render_scene_smart(engine, RENDER_SHOW_STATS);
	if (EXPERIMENTAL)
		mlx_sync(MLX_SYNC_WIN_CMD_COMPLETED, engine->ctx.win);
	return (0);
}
