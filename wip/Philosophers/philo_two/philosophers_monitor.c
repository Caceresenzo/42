/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_monitor.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:41:00 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/28 11:41:00 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	philosophers_monitor(t_man *root)
{
	t_man	*next;
	long	now;
	int		stop;

	while (!g_someone_is_dead)
	{
		now = x_millis();
		next = root;
		stop = 0;
		while (1)
		{
			stop |= !next->running;
			if (next->running
				&& now - next->param->time_to_die > next->last_meal)
			{
				philosophers_ring_end(root, next);
				return ;
			}
			if ((next = next->next) == root)
				break ;
		}
		if (stop)
			break ;
		usleep(1000);
	}
}
