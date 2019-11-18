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

#define WHITE 0xFFFFFF

void
	i_display_fps(t_engine *engine)
{
	char	*fps;
	char	*full;

	fps = ft_itoa(fps_counter_get());
	full = ft_strjoin("FPS: ", fps);
	mlx_string_put(engine->ctx.mlx, engine->ctx.win, 50, 50, WHITE, full);
	printf("FPS: %s\n", fps);
	free(fps);
	free(full);
}

int
	engine_loop(t_engine *engine)
{
	int		has_moved;

	if (engine->dirty)
	{
		fps_counter_start();
		render_scene(engine);
		mlx_put_image_to_window(engine->ctx.mlx, engine->ctx.win,
								engine->canvas->ptr, 0, 0);
		fps_counter_end();
		i_display_fps(engine);
		engine->dirty = 0;
		engine->was_dirty = 1;
	}
	else if (engine->was_dirty)
		mlx_string_put(engine->ctx.mlx, engine->ctx.win, 50, 80, WHITE, "OFF");
	else
		engine->was_dirty = 0;
	engine->player.move_speed = 0.01 * 5.0;
	engine->player.rot_speed = 0.01 * 5.0;
	has_moved = player_handle_mouvement(engine->map, &(engine->player));
	engine->dirty = engine->dirty || has_moved;
	return (0);
}
