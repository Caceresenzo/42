/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_computer_distance.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:48:45 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/20 12:48:45 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	ray_compute_distance(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map.x - ray->pos.x +
								(1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->perp_wall_dist = (ray->map.y - ray->pos.y +
								(1 - ray->step.y) / 2) / ray->dir.y;
}
