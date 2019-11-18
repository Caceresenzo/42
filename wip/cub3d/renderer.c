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
	ray->dir.x = player->dir.x + player->plane.x * camera_x;
	ray->dir.y = player->dir.y + player->plane.y * camera_x;
	ray->side_dist = (t_vec2d){ 0, 0 };
	ray->delta_dist.x = ABS(1 / ray->dir.x);
	ray->delta_dist.y = ABS(1 / ray->dir.y);
	ray->perp_wall_dist = 0;
	ray->step = (t_vec2d){ 0, 0 };
	ray->hit = 0;
	ray->side = 0;
}

static void
	i_renderer_display_texture(t_ray *ray, t_vec2i *tex_pos, t_image *tex)
{
	int		y;
	int		d;
	int		color;
	int		rgb[3];

	y = ray->result.start;
	while (y < ray->result.end)
	{
		d = y * 256;
		d -= ray->engine->ctx.height * 128;
		d += ray->result.line_height * 128;
		tex_pos->y = ((d * tex->height) / ray->result.line_height) / 256;
		image_get_pixel_raw(rgb, tex, tex_pos->x, tex_pos->y);
		image_set_pixel_raw(rgb, ray->engine->canvas, ray->x, y);
		y++;
	}
}

static void
	i_renderer_draw_texture(t_engine *engine, t_ray *ray, t_player *player)
{
	double		wall_x;
	t_image		*tex;
	t_vec2i		tex_pos;

	if (ray->side == 0)
	{
		tex = engine->map->wall_texs[NORTH];
		wall_x = player->pos.y + ray->perp_wall_dist * ray->dir.y;
	}
	else
	{
		tex = engine->map->wall_texs[SOUTH];
		wall_x = player->pos.x + ray->perp_wall_dist * ray->dir.x;
	}
	wall_x -= floor(wall_x);
	tex_pos.x = wall_x * tex->width;
	if (ray->side == 0 && ray->dir.x > 0)
		tex_pos.x = tex->width - tex_pos.x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		tex_pos.x = tex->width - tex_pos.x - 1;
	i_renderer_display_texture(ray, &tex_pos, tex);
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
	ray.engine = engine;
	ray.player = player;
	args.image = engine->canvas;
	while (x < engine->ctx.width)
	{
		ray.x = x;
		i_renderer_prepare_ray(engine->ctx.width, player, &ray, x);
		ray_compute(engine, &ray, engine->ctx.height, x);
		args.color = engine->map->roof_color;
		image_draw_vertical_line(args, x, 0, ray.result.start);
		args.color = engine->map->floor_color;
		image_draw_vertical_line(args, x, ray.result.end, engine->ctx.height);
		i_renderer_draw_texture(engine, &ray, player);
		x++;
	}
}
