/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_computer_limiter.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:49:09 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/20 12:49:09 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	ray_compute_set_limits(t_ray *ray)
{
	ray->out.height = (int)(ray->h / ray->perp_wall_dist);
	ray->out.start = -ray->out.height / 2 + ray->h / 2;
	ray->out.end = ray->out.height / 2 + ray->h / 2;
	if (ray->out.start < 0)
		ray->out.start = 0;
	if (ray->out.end >= ray->h)
		ray->out.end = ray->h - 1;
	ray->out.obj_type =
			map_get_object_type_at(ray->engine->map, ray->map.x, ray->map.y);
}
