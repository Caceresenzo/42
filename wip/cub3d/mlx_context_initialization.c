/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_context_initialization.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:00:52 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/12 15:00:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	*mlx_context_initialize(t_mlx_context *context)
{
	if (!(context->mlx = mlx_init()))
		return (NULL);
	context->graphics = 0;
	context->width = -1;
	context->height = -1;
	return (context);
}

void
	*mlx_window_initialize(t_engine *engine, t_mlx_context *context)
{
	char	*w_name;

	context->graphics = 1;
	w_name = ft_strjoin(WINDOW_NAME_BASE, engine->map->file);
	if (!(context->win = mlx_new_window(context->mlx, context->width,
										context->height, w_name)))
		return (NULL);
	free(w_name);
	return (context);
}

void
	*mlx_canvas_initialize(t_engine *eng, t_image **canvas_ptr)
{
	t_image *img;

	eng->ctx.width = ft_min(MAX_WINDOW_WIDTH, eng->ctx.width);
	eng->ctx.height = ft_min(MAX_WINDOW_HEIGHT, eng->ctx.height);
	img = image_create(eng->ctx.mlx, eng->ctx.width, eng->ctx.height);
	if (!(*canvas_ptr = img))
		return (NULL);
	return (canvas_ptr);
}
