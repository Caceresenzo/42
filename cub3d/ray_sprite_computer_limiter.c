/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sprite_computer_limiter.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:27:53 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 16:27:53 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	ray_sprite_compute_set_limits(t_ray *r)
{
	r->sout.h = ft_abs((int)(r->h / (r->trsnf.y))) / 1;
	r->sout.start_y = -r->sout.h / 2 + r->h / 2 + r->v_mv_scrn;
	if (r->sout.start_y < 0)
		r->sout.start_y = 0;
	r->sout.end_y = r->sout.h / 2 + r->h / 2 + r->v_mv_scrn;
	if (r->sout.end_y >= r->h)
		r->sout.end_y = r->h - 1;
	r->sout.w = ft_abs((int)(r->h / (r->trsnf.y))) / 1;
	r->sout.start_x = -r->sout.w / 2 + r->sprite_screen_x;
	if (r->sout.start_x < 0)
		r->sout.start_x = 0;
	r->sout.end_x = r->sout.w / 2 + r->sprite_screen_x;
	if (r->sout.end_x >= r->width)
		r->sout.end_x = r->width - 1;
}
