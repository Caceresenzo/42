/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phmm_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 17:15:59 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/13 17:15:59 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int
	phmm_start(t_table *table)
{
	int	err;

	if ((err = pthread_create(&(table->thr_death_monitor), NULL,
			(t_run)phmm_run_dead, table)))
		return (err);
	if (!(err = phmm_forks(table)))
	{
		phmm_shout(table, g_sem_wait_start);
		phmm_await(table, g_sem_stop_await);
	}
	phmm_kill(table);
	return (err);
}
