/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_renderer_player.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 15:42:26 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/24 15:42:26 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		g_minimap_player_color = 0xFFFFFF;
int		g_minimap_player_eyes_color = 0x8A2BE2;

void
	i_minimap_render_player_eyes(t_image *canvas, t_player *player,
								t_vec2i offset)
{
	t_drawer_line_args	args;
	t_vec2i				pos;
	t_vec2i				end;

	minimap_render_block(canvas, (t_vec2i) {
		(player->pos.x - 0.5 + player->dir.x) * MINIMAP_RES,
		(player->pos.y - 0.5 + player->dir.y) * MINIMAP_RES
	}, g_minimap_player_color, offset);
	args.image = canvas;
	args.color = g_minimap_player_eyes_color;
	pos = (t_vec2i) {
		offset.x + (player->pos.x * MINIMAP_RES),
		offset.y + (player->pos.y * MINIMAP_RES)
	};
	end.x = pos.x + (player->dir.x * MINIMAP_RES * 2);
	image_draw_horizontal_line(args, pos.x, end.x, pos.y);
	end.y = pos.y + (player->dir.y * MINIMAP_RES * 2);
	image_draw_vertical_line(args, pos.x, pos.y, end.y);
}

void
	minimap_render_player(t_image *canvas, t_player *player, t_vec2i offset)
{
	t_vec2i	pos;

	pos = (t_vec2i) {
		(player->pos.x - 0.5) * MINIMAP_RES,
		(player->pos.y - 0.5) * MINIMAP_RES
	};
	i_minimap_render_player_eyes(canvas, player, offset);
	minimap_render_block(canvas, pos, g_minimap_player_color, offset);
}
