/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_initialization.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 14:58:29 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/12 14:58:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void
	engine_init_module(t_engine *engine)
{
	char	*error;

	error = NULL;
	key_state_initialize();
	mouse_button_state_initialize();
	engine->dirty = 1;
	error = player_initialize(engine);
	if (error == NULL)
	{
		if (!map_sealing_check(engine->map,
					(t_vec2i) { engine->player.pos.x, engine->player.pos.y }))
			error = e("Map is not sealed");
	}
	if (error != NULL)
		engine_error(error);
}

static void
	engine_init_members(t_engine *engine)
{
	engine->canvas = NULL;
	engine->map = NULL;
	engine->dirty = 1;
	engine->was_dirty = 0;
}

static void
	engine_hook(int event, int (*callback)(), t_engine *engine)
{
	mlx_hook(engine->ctx.win, event, 0, callback, engine);
}

int
	engine_initialize(char *path, int save_arg)
{
	t_engine	engine;

	engine_init_members(engine_global_set(&engine));
	if (!mlx_context_initialize(&engine.ctx))
		return (-1);
	map_load(&engine, path);
	engine_init_module(&engine);
	if (!mlx_canvas_initialize(&engine, &(engine.canvas)))
		return (-1);
	if (save_arg)
		mlx_export_bmp(&engine);
	else
	{
		if (!mlx_window_initialize(&engine, &engine.ctx))
			return (-1);
		engine_hook(X_EVENT_KEY_PRESS, &engine_on_key_pressed, &engine);
		engine_hook(X_EVENT_KEY_RELEASE, &engine_on_key_released, &engine);
		engine_hook(X_EVENT_MOUSE_PRESS, &engine_on_mouse_pressed, &engine);
		engine_hook(X_EVENT_MOUSE_RELEASE, &engine_on_mouse_released, &engine);
		engine_hook(X_EVENT_MOUSE_MOVE, &engine_on_mouse_move, &engine);
		engine_hook(X_EVENT_EXIT, &engine_on_exit, &engine);
		mlx_loop_hook(engine.ctx.mlx, &engine_loop, &engine);
		mlx_loop(engine.ctx.mlx);
	}
	return (engine_handle_exit(&engine, 1));
}
