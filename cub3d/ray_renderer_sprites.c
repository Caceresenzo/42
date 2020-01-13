/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_renderer_sprites.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:43:15 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/21 13:43:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	ray_renderer_sprite_draw(t_engine *eng, t_ray *ray)
{
	t_map	*map;
	size_t	index;

	if (!ray->zbuffer)
		return ;
	map = eng->map;
	if (map->sprite_count == 0)
		return ;
	ray_sprite_precomputer_order(&(eng->player), eng->map);
	index = 0;
	while (index < map->sprite_count)
	{
		ray_sprite_compute(ray, map->sprts[map->spr_ordr[index]]);
		ray_renderer_sprite_draw_texture(ray, map->sprite, eng->canvas);
		index++;
	}
}

/*
** For: ray_renderer_sprite_draw_texture
** due to norminette problem, the "a" local value correspond
** to the "d" and "color" local value where there are represented
** by the x and y member of the vector type.
*/

void
	ray_renderer_sprite_draw_texture(t_ray *r, t_image *img, t_image *canvas)
{
	t_vec2i	tex;
	t_vec2i	p;
	t_vec2i	a;

	p.x = r->sout.start_x;
	while (p.x < r->sout.end_x)
	{
		tex.x = (int)(256 * (p.x - (-r->sout.w / 2 + r->sprite_screen_x))
				* img->width / r->sout.w) / 256;
		if (r->trsnf.y > 0 && p.x > 0 &&
				p.x < r->width && r->trsnf.y < r->zbuffer[p.x])
		{
			p.y = r->sout.start_y;
			while (p.y < r->sout.end_y)
			{
				a.x = (p.y - r->v_mv_scrn) * 256 - r->h * 128 + r->sout.h * 128;
				tex.y = ((a.x * img->height) / r->sout.h) / 256;
				a.y = img->pic[img->width * tex.y + tex.x];
				if ((a.y & 0X00FFFFFF) != 0)
					canvas->pic[(p.y * canvas->line_unit) + (p.x)] = a.y;
				p.y += 1;
			}
		}
		p.x += 1;
	}
}
