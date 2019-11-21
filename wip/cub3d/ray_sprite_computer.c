/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sprite_computer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:07:58 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 16:07:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	ray_sprite_compute(t_ray *ray, t_game_object *sprite_obj)
{
	ray_sprite_compute_matrix(ray, sprite_obj);
	ray_sprite_compute_set_limits(ray);
}
