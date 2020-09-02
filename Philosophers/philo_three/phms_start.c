/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phms_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 17:41:03 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/13 17:41:03 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int
	phms_start_monitors(t_seat *seat)
{
	int	err;

	if ((err = pthread_create(&(seat->man->thr_monitor), NULL,
			(t_run)phms_run_starvation, seat)))
		return (err);
	if ((err = pthread_create(&(seat->man->thr_stop_monitor), NULL,
			(t_run)phms_run_stop, seat)))
		return (err);
	return (0);
}

void
	phms_start(t_table *table, int index)
{
	t_seat	seat;
	int		err;

	seat = (t_seat){
		.table = table,
		.index = index,
		.man = &(table->mans[index])
	};
	sem_wait(g_sem_wait_start);
	if ((err = phms_start_monitors(&seat)))
		err_errno(err, seat.man->id);
	if (!err)
		ph_runnable(seat.man);
	phms_exit(&seat);
}
