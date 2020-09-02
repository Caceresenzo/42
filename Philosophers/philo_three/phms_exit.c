/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phms_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 17:23:27 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/13 17:23:27 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	phms_exit(t_seat *seat)
{
	sem_post(g_sem_stop_await);
	(void)seat;
	pthread_detach(seat->man->thr_monitor);
	pthread_detach(seat->man->thr_stop_monitor);
	exit(0);
}
