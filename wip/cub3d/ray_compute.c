/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_compute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 14:48:01 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/18 14:48:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		g_object_color[] = {
	0,
	0xFF0000,
	0x00FF00,
	0x0000FF
};

void
	ray_compute_pre(t_engine *engine, t_ray *ray, t_vec2d *pos,
					t_vec2i *map_pos)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (pos->x - map_pos->x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (map_pos->x + 1.0 - pos->x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (pos->y - map_pos->y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (map_pos->y + 1.0 - pos->y) * ray->delta_dist.y;
	}
}

void
	ray_compute_step(t_engine *engine, t_ray *ray, t_vec2i *map_pos)
{
	while (!(ray->hit))
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			map_pos->x += ray->step.x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			map_pos->y += ray->step.y;
			ray->side = 1;
		}
		if (!map_is_empty_at(engine->map, map_pos->x, map_pos->y))
			ray->hit = 1;
	}
}

void
	ray_compute_result(t_engine *engine, t_ray *ray, t_vec2i *map_pos,
						int height)
{
	int		color;

	ray->result.line_height = (int)(height / ray->perp_wall_dist);
	ray->result.start = -ray->result.line_height / 2 + height / 2;
	ray->result.end = ray->result.line_height / 2 + height / 2;
	if (ray->result.start < 0)
		ray->result.start = 0;
	if (ray->result.end >= height)
		ray->result.end = height - 1;
	color = map_get_object_type_at(engine->map, map_pos->x, map_pos->y);
	color = g_object_color[color];
	if (ray->side == 1)
		color = color / 2;
	ray->result.color = color;
}

void
	ray_compute(t_engine *engine, t_ray *ray, int height, int x)
{
	t_vec2d *pos;
	t_vec2i	map_pos;

	pos = &(ray->player->pos);
	map_pos = (t_vec2i){ (int)pos->x, (int)pos->y };
	ray_compute_pre(engine, ray, pos, &map_pos);
	ray_compute_step(engine, ray, &map_pos);
	if (ray->side == 0)
		ray->perp_wall_dist = (map_pos.x - pos->x +
								(1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (map_pos.y - pos->y +
								(1 - ray->step.y) / 2) / ray->dir.y;
	ray_compute_result(engine, ray, &map_pos, height);
}
