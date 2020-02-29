/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_millis.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:44:00 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 18:44:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long	g_start = -1;

long
	x_millis(void)
{
	struct timeval	tv;
	long			millis;

	gettimeofday(&tv, NULL);
	millis = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	if (g_start == -1)
		g_start = millis;
	return (millis - g_start);
}
