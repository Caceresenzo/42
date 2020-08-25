/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phm_run_starvation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 17:50:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/13 17:50:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	phm_run_starvation(t_man *man)
{
	long	time_to_die;
	long	now;
	long	last;

	time_to_die = g_params.time_to_die;
	while (!g_someone_is_dead && !man->stopped)
	{
		pthread_mutex_lock(&(man->mutex));
		last = man->last_meal;
		pthread_mutex_unlock(&(man->mutex));
		now = ph_millis();
		if (man->stopped)
			break ;
		if (now - time_to_die > last)
		{
			ph_update(man, dead);
			break ;
		}
		usleep(DELAY_MONITOR);
	}
}
