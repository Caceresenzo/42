/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_exit_handler.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:33:40 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/22 15:33:40 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	engine_handle_exit(t_engine *engine, int auto_exit)
{
	if (engine->map)
		map_destroy(engine->ctx.mlx, &(engine->map));
	if (engine->canvas)
		image_destroy_null(engine->ctx.mlx, &(engine->canvas));
	if (auto_exit)
		exit(0);
	return (0);
}
