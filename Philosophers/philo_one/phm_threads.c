/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phm_threads.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 17:09:50 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/13 17:09:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int
	phm_threads(t_table *table)
{
	int		index;
	int		err;
	t_man	*man;

	index = 0;
	while (index < g_params.nbr_of_philo)
	{
		man = &(table->mans[index]);
		if ((err = pthread_create(&(man->thr), NULL,
			(t_run)ph_runnable, man)))
			return (err);
		man->is |= IS_THREAD;
		if ((err = pthread_create(&(man->thr_monitor), NULL,
			(t_run)phm_run_starvation, man)))
			return (err);
		man->is |= IS_MONITOR;
		index++;
	}
	return (0);
}
