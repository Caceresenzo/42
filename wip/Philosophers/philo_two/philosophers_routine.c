/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_routine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:12:58 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 18:12:58 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void
	man_sleep(t_man *man, int millis)
{
	long end;

	if (!man->running)
		return ;
	end = x_millis() + millis;
	while (1)
		if (!(man->running && end > x_millis()))
			break ;
}

static void
	man_start_sleep(t_man *man)
{
	long millis;

	millis = (man->param->time_to_die / man->param->nbr_of_philo)
				* (man->id - 1);
	man_sleep(man, millis);
}

void
	philosophers_routine(t_man *man)
{
	while (man->wait_start)
		man_sleep(man, 0);
	man_start_sleep(man);
	while (man->running && !g_someone_is_dead)
	{
		sem_wait(man->forks);
		philosophers_status_update(man, took_a_fork);
		sem_wait(man->forks);
		philosophers_status_update(man, eating);
		man->last_meal = x_millis();
		man_sleep(man, man->param->time_to_eat);
		sem_post(man->forks);
		sem_post(man->forks);
		man->eat_count += 1;
		if (man->param->nbr_must_eat != -1
				&& man->eat_count >= man->param->nbr_must_eat)
			break ;
		philosophers_status_update(man, sleeping);
		man_sleep(man, man->param->time_to_sleep);
		philosophers_status_update(man, thinking);
	}
	man->running = 0;
}
