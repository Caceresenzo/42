/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_renderer_default.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:51:14 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 13:51:14 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	ray_renderer_draw_default(t_engine *engine, t_ray *ray)
{
	int		y;
	size_t	offset;

	y = ray->out.start;
	offset = y * engine->canvas->line_unit + ray->x;
	while (y < ray->out.end)
	{
		engine->canvas->pic[offset] = (y + ray->x) % 4 < 2 ? 0xC71585 : 0x0;
		offset += engine->canvas->line_unit;
		y++;
	}
}
