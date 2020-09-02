/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 17:32:17 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/13 17:32:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define IS_MALLOC	1
#define IS_SEM		2
#define IS_THREAD	4

int
	ph_table_init_malloc(t_table *table)
{
	int	index;

	if (!(table->pids = ft_malloc(g_params.nbr_of_philo * sizeof(pid_t))))
		return (ENOMEM);
	if (!(table->mans = ft_malloc(g_params.nbr_of_philo * sizeof(t_man))))
		return (ENOMEM);
	index = 0;
	while (index < g_params.nbr_of_philo)
	{
		table->mans[index].id = index + 1;
		table->mans[index].is |= IS_MALLOC;
		index++;
	}
	return (0);
}

int
	ph_table_init(t_table *table)
{
	int	index;
	int err;

	if ((err = ph_table_init_malloc(table)))
		return (err);
	index = 0;
	while (index < g_params.nbr_of_philo)
	{
		if ((table->mans[index].sem = ph_sem_open_man(index)) == SEM_FAILED)
			return (err);
		table->mans[index].is |= IS_SEM;
		index++;
	}
	return (0);
}

void
	ph_table_destroy(t_table *table)
{
	int		index;
	t_man	*man;

	index = 0;
	while (index < g_params.nbr_of_philo)
	{
		if ((man = &(table->mans[index]))->is & IS_SEM)
			ph_sem_destroy_man(&(man->sem), index);
		index++;
	}
	pthread_detach(table->thr_death_monitor);
	free(table->mans);
	free(table->pids);
}
