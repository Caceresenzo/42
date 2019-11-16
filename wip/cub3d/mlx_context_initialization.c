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
	CHECK_PTR(context->win = mlx_new_window(context->mlx, context->width,
												context->height, WINDOW_NAME));
	return (context);
}
