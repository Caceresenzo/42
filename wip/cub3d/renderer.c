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

static void
	i_renderer_prepare_ray(int width, t_player *player, t_ray *ray, int x)
{
	double camera_x;

	camera_x = 2 * x / (double)(width) - 1;
	ray->ray_dir.x = player->dir.x + player->plane.x * camera_x;
	ray->ray_dir.y = player->dir.y + player->plane.y * camera_x;
	ray->side_dist = (t_vec2d){ 0, 0 };
	ray->delta_dist.x = ABS(1 / ray->ray_dir.x);
	ray->delta_dist.y = ABS(1 / ray->ray_dir.y);
	ray->perp_wall_dist = 0;
	ray->step = (t_vec2d){ 0, 0 };
	ray->hit = 0;
	ray->side = 0;
}

void
	render_scene(t_engine *engine)
{
	int					x;
	t_player			*player;
	t_ray				ray;
	t_drawer_line_args	args;

	x = 0;
	player = &(engine->player);
	ray.player = player;
	args.image = engine->canvas;
	while (x < engine->ctx.width)
	{
		i_renderer_prepare_ray(engine->ctx.width, player, &ray, x);
		ray_compute(engine, &ray, engine->ctx.height, x);
		args.color = engine->map->roof_color;
		image_draw_vertical_line(args, x, 0, ray.result.start);
		args.color = engine->map->floor_color;
		image_draw_vertical_line(args, x, ray.result.end, engine->ctx.height);
		args.color = ray.result.color;
		image_draw_vertical_line(args, x, ray.result.start, ray.result.end);
		x++;
	}
}
