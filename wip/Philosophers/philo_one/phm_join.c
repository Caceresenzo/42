/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phm_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 12:00:29 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/11 12:00:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	phm_join(t_table *table)
{
	int		index;
	t_man	*man;

	index = -1;
	while (++index < g_params.nbr_of_philo)
	{
		man = &(table->mans[index]);
		if (man->is & IS_THREAD)
			pthread_join(man->thr, NULL);
		if (man->is & IS_MONITOR)
			pthread_join(man->thr_monitor, NULL);
	}
}
