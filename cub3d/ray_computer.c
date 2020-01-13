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

void
	ray_compute(t_ray *ray_ptr)
{
	ray_compute_initialize(ray_ptr);
	ray_compute_find_side(ray_ptr);
	ray_compute_dda(ray_ptr);
	ray_compute_distance(ray_ptr);
	ray_compute_set_limits(ray_ptr);
	if (ray_ptr->zbuffer)
		ray_ptr->zbuffer[ray_ptr->x] = ray_ptr->perp_wall_dist;
}
