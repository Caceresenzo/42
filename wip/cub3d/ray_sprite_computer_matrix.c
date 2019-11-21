/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_sprite_computer_matrix.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:28:28 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 16:28:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	ray_sprite_compute_matrix(t_ray *r, t_game_object *spr)
{
	t_player	*p;

	p = r->player;
	r->spr.x = spr->pos.x - p->pos.x;
	r->spr.y = spr->pos.y - p->pos.y;
	r->inv_d = 1.0 / (p->plane.x * p->dir.y - p->dir.x * p->plane.y);
	r->trsnf.x = r->inv_d * (p->dir.y * r->spr.x - p->dir.x * r->spr.y);
	r->trsnf.y = r->inv_d * (-p->plane.y * r->spr.x + p->plane.x * r->spr.y);
	r->sprite_screen_x = (int)((r->width / 2) * (1 + r->trsnf.x / r->trsnf.y));
	r->v_mv_scrn = (int)(0.0 / r->trsnf.y);
}
