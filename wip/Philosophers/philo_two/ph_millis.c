/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_millis.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/10 19:08:37 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/10 19:08:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>

#include "philosophers.h"

long
	ph_millis(void)
{
	static long		start = -1;
	struct timeval	tv;
	long			local_start;
	long			millis;

	gettimeofday(&tv, NULL);
	millis = (tv.tv_sec) * 1000 + (tv.tv_usec) / 1000;
	sem_wait(g_sem_millis);
	if (start == -1)
		start = millis;
	local_start = start;
	sem_post(g_sem_millis);
	return (millis - local_start);
}
