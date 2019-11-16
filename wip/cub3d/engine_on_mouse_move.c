/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_on_mouse_move.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 17:23:50 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/12 17:23:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	engine_on_mouse_move(int x, int y, t_engine *engine)
{
	printf("EVENT: on_mouse_move: x = %d, y = %d\n", x, y);
	mlx_pixel_put(engine->ctx.mlx, engine->ctx.win, x, y, 0xFF0000);
	return (0);
}
