/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_positions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/24 13:53:45 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/24 13:53:45 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "maths.h"
#include "cub3d.h"
#include "mouse.h"

t_vec2i	g_mouse_last_click_position = (t_vec2i) { -1, -1 };
t_vec2i	g_mouse_current_position = (t_vec2i) { -1, -1 };

void
	mouse_pos_last_click_update(int x, int y)
{
	g_mouse_last_click_position.x = x;
	g_mouse_last_click_position.y = y;
	mouse_pos_current_update(x, y);
}

void
	mouse_pos_current_update(int x, int y)
{
	g_mouse_current_position.x = x;
	g_mouse_current_position.y = y;
}

t_vec2i
	mouse_pos_last_click_get(void)
{
	return (g_mouse_last_click_position);
}

t_vec2i
	mouse_pos_current_get(void)
{
	return (g_mouse_current_position);
}

void
	mouse_pos_update_last_to_current(void)
{
	g_mouse_last_click_position = g_mouse_current_position;
}
