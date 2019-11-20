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

void	*mlx_context_initialize(t_mlx_context *context)
{
	CHECK_PTR(context->mlx = mlx_init());
	return (context);
}

void	*mlx_window_initialize(t_mlx_context *context)
{
	context->w_dim.w = MIN(MAX_WINDOW_WIDTH, context->width);
	context->w_dim.h = MIN(MAX_WINDOW_HEIGHT, context->height);
	CHECK_PTR(context->win = mlx_new_window(context->mlx, context->w_dim.w,
											context->w_dim.h, WINDOW_NAME));
	return (context);
}

void	*mlx_canvas_initialize(t_engine *eng, t_map *map, t_image **canvas_ptr)
{
	t_image *img;

	img = image_create(eng, eng->ctx.width, eng->ctx.height);
	CHECK_PTR(*canvas_ptr = img);
	return (canvas_ptr);
}
