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

#define HOOK(event, callback) mlx_hook(eng.ctx.win, event, 0, callback, &eng);

static void
	engine_init_module(t_engine *engine)
{
	char	*error;

	error = NULL;
	key_state_initialize();
	engine->dirty = 1;
	error = player_initialize(engine);
	if (error == NULL)
	{
		if (!map_sealing_check(engine->map,
					(t_vec2i) { engine->player.pos.x, engine->player.pos.y }))
			error = E("Map is not sealed");
	}
	map_dump(engine->map);
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

int
	engine_initialize(char *path, int save_arg)
{
	t_engine	eng;

	engine_init_members(&eng);
	engine_global_set(&eng);
	CHECK_PTR_DEF(mlx_context_initialize(&eng.ctx), -1);
	map_load(&eng, path);
	engine_init_module(&eng);
	CHECK_PTR_DEF(mlx_canvas_initialize(&eng, &(eng.canvas)), -1);
	if (save_arg)
		mlx_export_bmp(&eng);
	else
	{
		CHECK_PTR_DEF(mlx_window_initialize(&eng, &eng.ctx), -1);
		HOOK(X_EVENT_KEY_PRESS, &engine_on_key_pressed);
		HOOK(X_EVENT_KEY_RELEASE, &engine_on_key_released);
		HOOK(X_EVENT_MOUSE_PRESS, &engine_on_mouse_pressed);
		HOOK(X_EVENT_MOUSE_RELEASE, &engine_on_mouse_released);
		HOOK(X_EVENT_MOUSE_MOVE, &engine_on_mouse_move);
		HOOK(X_EVENT_EXIT, &engine_on_exit);
		mlx_loop_hook(eng.ctx.mlx, &engine_loop, &eng);
		mlx_loop(eng.ctx.mlx);
	}
	return (engine_handle_exit(&eng, 1));
}
