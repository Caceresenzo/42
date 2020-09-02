/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:17:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/11 13:17:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void
	create(int *err, t_mutex *mutex)
{
	if (!*err)
		*err = pthread_mutex_init(mutex, NULL);
}

static void
	destroy(t_mutex *mutex)
{
	pthread_mutex_destroy(mutex);
}

int
	phm_init(void)
{
	int err;

	err = 0;
	create(&err, &g_mutex_stdout);
	create(&err, &g_mutex_millis);
	create(&err, &g_mutex_dead);
	return (err);
}

void
	phm_destroy(void)
{
	destroy(&g_mutex_stdout);
	destroy(&g_mutex_millis);
	destroy(&g_mutex_dead);
}
