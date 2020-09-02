/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phms_run_starvation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 17:50:41 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/13 17:50:41 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	phms_run_starvation(t_seat *seat)
{
	t_man	*man;
	long	time_to_die;
	long	now;
	long	last;

	man = seat->man;
	time_to_die = g_params.time_to_die;
	while (1)
	{
		sem_wait(man->sem);
		last = man->last_meal;
		sem_post(man->sem);
		now = ph_millis();
		if (now - time_to_die > last)
			break ;
		usleep(DELAY_MONITOR);
	}
	ph_update(man, dead);
	phms_exit(seat);
}
