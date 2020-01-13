/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_renderer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:34:57 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/20 14:34:57 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	(*g_renderer[])(t_engine *, t_ray *) = {
	NULL,
	&ray_renderer_draw_wall,
	NULL,
	NULL,
	NULL
};

void
	ray_render_scene(t_engine *engine)
{
	t_ray				ray;
	t_ray				*ray_ptr;
	t_drawer_line_args	args;
	void				(*sub_renderer)(t_engine *, t_ray *);

	args.image = engine->canvas;
	ray_ptr = &ray;
	ray_compute_initialize_struct(ray_ptr, engine);
	ray.x = 0;
	while (ray.x < ray.width)
	{
		ray_compute(ray_ptr);
		sub_renderer = g_renderer[ray.out.obj_type];
		if (sub_renderer == NULL)
			sub_renderer = &ray_renderer_draw_default;
		sub_renderer(engine, ray_ptr);
		args.color = engine->map->roof_color;
		image_draw_vertical_line(args, ray.x, 0, ray.out.start);
		args.color = engine->map->floor_color;
		image_draw_vertical_line(args, ray.x, ray.out.end, engine->ctx.height);
		ray.x += 1;
	}
	ray_renderer_sprite_draw(engine, &ray);
	free(ray.zbuffer);
	ray.zbuffer = NULL;
}
