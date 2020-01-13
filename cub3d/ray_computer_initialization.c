/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_computer_initialization.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:47:11 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/20 12:47:11 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	ray_compute_initialize_struct(t_ray *ray_ptr, t_engine *engine)
{
	ray_ptr->engine = engine;
	ray_ptr->player = &(engine->player);
	ray_ptr->width = engine->ctx.width;
	ray_ptr->h = engine->ctx.height;
	ray_ptr->zbuffer = malloc(ray_ptr->width * sizeof(double));
}

void
	ray_compute_initialize(t_ray *ray)
{
	ray->pos = (t_vec2d) { ray->player->pos.x, ray->player->pos.y };
	ray->camera_x = 2 * ray->x / (double)(ray->width) - 1;
	ray->dir.x = ray->player->dir.x + ray->player->plane.x * ray->camera_x;
	ray->dir.y = ray->player->dir.y + ray->player->plane.y * ray->camera_x;
	ray->map = (t_vec2i) { ray->pos.x, ray->pos.y };
	ray->delta.x = sqrt(1 +
						(ray->dir.y * ray->dir.y) / (ray->dir.x * ray->dir.x));
	ray->delta.y = sqrt(1 +
						(ray->dir.x * ray->dir.x) / (ray->dir.y * ray->dir.y));
	ray->hit = 0;
}
