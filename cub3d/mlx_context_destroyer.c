/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_context_destroyer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:00:52 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/12 15:00:52 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	mlx_context_window_destroy(t_mlx_context *context)
{
	if (context->graphics)
		mlx_destroy_window(context->mlx, context->win);
	context->graphics = 0;
}
