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
	while (man->running && end > x_millis())
		;
}

void
	philosophers_routine(t_man *man)
{
	while (!man->running)
		;
	while (man->running && !g_someone_is_dead)
	{
		fork_grab(man->id % 2 == 0 ? man->fork_l : man->fork_r);
		philosophers_status_update(man, took_a_fork);
		fork_grab(man->id % 2 == 0 ? man->fork_r : man->fork_l);
		philosophers_status_update(man, eating);
		man->last_meal = x_millis();
		man_sleep(man, man->param->time_to_eat);
		fork_release(man->fork_l);
		fork_release(man->fork_r);
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
