/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_renderer_walls.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:40:05 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 13:40:05 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	ray_renderer_draw_wall(t_engine *engine, t_ray *ray)
{
	double		wall_x;
	t_image		*tex;
	t_vec2i		tex_pos;

	if (ray->side == 0)
		wall_x = ray->player->pos.y + ray->perp_wall_dist * ray->dir.y;
	else
		wall_x = ray->player->pos.x + ray->perp_wall_dist * ray->dir.x;
	wall_x -= floor(wall_x);
	tex = ray_renderer_wall_texture_finder(engine->map, ray);
	tex_pos.x = wall_x * tex->width;
	if (ray->side == 0 && ray->dir.x > 0)
		tex_pos.x = tex->width - tex_pos.x - 1;
	if (ray->side == 1 && ray->dir.y < 0)
		tex_pos.x = tex->width - tex_pos.x - 1;
	ray_renderer_wall_draw_texture(ray, &tex_pos, tex);
}

void
	ray_renderer_wall_draw_texture(t_ray *ray, t_vec2i *tex_pos, t_image *tex)
{
	int		y;
	int		d;
	size_t	offset;

	y = ray->out.start;
	while (y < ray->out.end)
	{
		d = y * 256;
		d -= ray->engine->ctx.height * 128;
		d += ray->out.height * 128;
		tex_pos->y = ((d * tex->height) / ray->out.height) / 256;
		offset = (y * ray->engine->canvas->line_unit) + (ray->x);
		ray->engine->canvas->pic[offset] =
						tex->pic[(tex_pos->y * tex->line_unit) + (tex_pos->x)];
		y++;
	}
}

t_image
	*ray_renderer_wall_texture_finder(t_map *map, t_ray *ray)
{
	if (ray->side == 0)
	{
		if (ray->dir.x > 0)
			return (map->wall_texs[WEST]);
		else
			return (map->wall_texs[EAST]);
	}
	if (ray->side == 1)
	{
		if (ray->dir.y < 0)
			return (map->wall_texs[SOUTH]);
		else
			return (map->wall_texs[NORTH]);
	}
	return (NULL);
}
