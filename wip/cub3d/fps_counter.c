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

void
	fps_counter_start(void)
{
	g_current_ticks = clock();
}

void
	fps_counter_end(void)
{
	g_delta_ticks = clock() - g_current_ticks;
}

int
	fps_counter_get(void)
{
	if (g_delta_ticks > 0)
		return (CLOCKS_PER_SEC / g_delta_ticks);
	return (-1);
}
