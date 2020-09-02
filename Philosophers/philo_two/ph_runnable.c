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
	eat(bool countdown, t_man *mn)
{
	bool	ret;

	if (!(ret = countdown && (mn->eat_count++) >= g_params.nbr_must_eat))
	{
		sem_wait(g_sem_grab);
		sem_wait(g_sem_forks);
		ph_update(mn, took_a_fork);
		sem_wait(g_sem_forks);
		ph_update(mn, took_a_fork);
		sem_post(g_sem_grab);
		ph_update(mn, eating);
		ph_sleep(g_params.time_to_eat);
		sem_post(g_sem_forks);
		sem_post(g_sem_forks);
	}
	return (ret);
}

void
	ph_runnable(t_man *mn)
{
	bool	countdown;

	countdown = g_params.nbr_must_eat != -1;
	while (!g_someone_is_dead && !mn->stopped)
	{
		if (eat(countdown, mn))
			break ;
		ph_update(mn, sleeping);
		ph_sleep(g_params.time_to_sleep);
		ph_update(mn, thinking);
	}
	mn->stopped = true;
}
