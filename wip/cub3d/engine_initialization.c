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

#define HOOK(event, callback) mlx_hook(eng.ctx.win, event, 0, callback, &eng);=

int
	engine_initialize(char *path, int save_arg)
{
	t_engine	eng;

	CHECK_PTR_DEF(mlx_context_initialize(&eng.ctx), -1);
	map_load(&eng, path);
	CHECK_PTR_DEF(mlx_window_initialize(&eng.ctx), -1);

	for (int i = 0; i < eng.map->size.h; i++)
	{
		for (int j = 0; j < eng.map->size.w; j++)
		{
			t_game_object obj = eng.map->objs[i][j];
			if (obj.type == OBJ_EMPTY)
				printf("  ");
			else if (obj.type == OBJ_WALL)
				printf("O ");
			else if (obj.type == OBJ_PLAYER)
				printf("P ");
			else
				printf("%d ", obj.type);
		}
		printf("\n");
	}
	printf("\n");



//	HOOK(X_EVENT_KEY_PRESS, &engine_on_key_pressed);
//	HOOK(X_EVENT_KEY_RELEASE, &engine_on_key_released);
//	HOOK(X_EVENT_MOUSE_PRESS, &engine_on_mouse_pressed);
//	HOOK(X_EVENT_MOUSE_RELEASE, &engine_on_mouse_released);
//	HOOK(X_EVENT_MOUSE_MOVE, &engine_on_mouse_move);
//	HOOK(X_EVENT_EXIT, &engine_on_exit);
//	mlx_loop_hook(eng.ctx.mlx, &engine_loop, &eng);
//	mlx_loop(eng.ctx.mlx);
	return (0);
}
