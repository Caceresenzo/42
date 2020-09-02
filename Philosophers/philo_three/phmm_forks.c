/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phmm_forks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 17:09:50 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/13 17:09:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int
	phmm_forks(t_table *table)
{
	int		index;
	pid_t	pid;
	long	start;

	index = 0;
	start = ph_millis();
	while (index < g_params.nbr_of_philo)
	{
		table->mans[index].start = start;
		table->mans[index].last_meal = start;
		if ((pid = fork()) == -1)
			return (errno);
		else if (pid == 0)
			phms_start(table, index);
		else
			table->pids[table->child_count++] = pid;
		index++;
	}
	return (0);
}
