/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:18:40 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/18 13:18:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	render_scene(t_engine *engine)
{
	ray_render_scene(engine);
	if (engine->map->render_minimap && BONUS)
		minimap_render(engine->canvas, &(engine->player), engine->map);
	if (engine->ctx.graphics)
		mlx_put_image_to_window(engine->ctx.mlx, engine->ctx.win,
							engine->canvas->ptr, 0, 0);
}

void
	render_scene_smart(t_engine *engine, int show_stats)
{
	if (engine->dirty)
	{
		if (RENDER_DO_FRAMING)
		{
			if (engine->canvas)
				image_destroy_null(engine->ctx.mlx, &(engine->canvas));
			mlx_canvas_initialize(engine, &(engine->canvas));
		}
		fps_counter_start();
		render_scene(engine);
		fps_counter_end();
		if (show_stats)
			render_display_fps(engine);
		engine->dirty = 0;
		engine->was_dirty = 1;
	}
	else if (engine->was_dirty)
	{
		if (show_stats)
			mlx_string_put(engine->ctx.mlx, engine->ctx.win, 50, 80,
							0xFFFFFF, "OFF");
	}
	else
		engine->was_dirty = 0;
}

void
	render_display_fps(t_engine *engine)
{
	char	*fps;
	char	*full;

	fps = ft_itoa(fps_counter_get());
	full = ft_strjoin("FPS: ", fps);
	mlx_string_put(engine->ctx.mlx, engine->ctx.win, 50, 50, 0xFFFFFF, full);
	free(fps);
	free(full);
}
