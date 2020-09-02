/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_runnable.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 11:47:46 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/11 11:47:46 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static bool
	eat(bool countdown, t_man *mn, t_mutex *a, t_mutex *b)
{
	bool	ret;

	if (!(ret = countdown && (mn->eat_count++) >= g_params.nbr_must_eat))
	{
		pthread_mutex_lock(a);
		ph_update(mn, took_a_fork);
		pthread_mutex_lock(b);
		ph_update(mn, took_a_fork);
		ph_update(mn, eating);
		ph_sleep(g_params.time_to_eat);
		pthread_mutex_unlock(a);
		pthread_mutex_unlock(b);
	}
	return (ret);
}

void
	ph_runnable(t_man *mn)
{
	bool	countdown;
	t_mutex	*a;
	t_mutex	*b;

	countdown = g_params.nbr_must_eat != -1;
	a = mn->forks[0 + (mn->id % 2)];
	b = mn->forks[1 - (mn->id % 2)];
	while (!g_someone_is_dead)
	{
		if (eat(countdown, mn, a, b))
			break ;
		ph_update(mn, sleeping);
		ph_sleep(g_params.time_to_sleep);
		ph_update(mn, thinking);
	}
	mn->stopped = true;
}
