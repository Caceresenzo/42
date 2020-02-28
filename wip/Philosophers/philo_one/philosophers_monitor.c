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

	while (1)
	{
		now = x_millis();
		next = root;
		while (1)
		{
			if (next->running
				&& now - next->param->time_to_die > next->last_meal)
			{
				philosophers_ring_end(root, next);
				return ;
			}
			if ((next = next->next) == root)
				break ;
		}
		usleep(8 * 1000);
	}
}
