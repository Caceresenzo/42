/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:23:28 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/18 18:23:28 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

clock_t g_current_ticks;
clock_t g_delta_ticks;
double	g_last_tick;

void
	fps_counter_start(void)
{
	if (!BONUS)
		return ;
	g_current_ticks = clock();
}

void
	fps_counter_end(void)
{
	if (!BONUS)
		return ;
	g_delta_ticks = clock() - g_current_ticks;
	if (g_delta_ticks > 0)
		g_last_tick = (double)g_delta_ticks / 1000000;
}

int
	fps_counter_get(void)
{
	if (!BONUS)
		return (-1);
	if (g_delta_ticks > 0)
		return (CLOCKS_PER_SEC / g_delta_ticks);
	return (-1);
}

double
	fps_counter_get_tick(void)
{
	if (!BONUS)
		return (0.02);
	return (g_last_tick);
}
