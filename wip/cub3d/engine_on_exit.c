/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_on_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 11:42:00 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/13 11:42:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	engine_on_exit(t_engine *engine)
{
	printf("EVENT: engine_on_exit\n");
	if (engine->ctx.win)
	{
		mlx_destroy_window(engine->ctx.mlx, engine->ctx.win);
		engine->ctx.win = NULL;
		exit(0);
	}
	return (0);
}
