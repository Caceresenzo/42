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

static int
	safe_range(int index)
{
	if (index >= g_params.nbr_of_philo)
		return (0);
	if (index < 0)
		return (g_params.nbr_of_philo - 1);
	return (index);
}

int
	ph_table_init_malloc(t_table *table)
{
	int	index;

	if (!(table->mans = ft_malloc(g_params.nbr_of_philo * sizeof(t_man))))
		return (ENOMEM);
	if (!(table->forks = ft_malloc(g_params.nbr_of_philo * sizeof(t_mutex))))
	{
		free(table->mans);
		return (ENOMEM);
	}
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
		if ((err = pthread_mutex_init(&(table->mans[index].mutex), NULL)))
			return (err);
		table->mans[index].is |= IS_MUTEX;
		if ((err = pthread_mutex_init(&(table->forks[index]), NULL)))
			return (err);
		table->mans[index].is |= IS_FORK;
		table->mans[index].forks[0] = &(table->forks[safe_range(index + 0)]);
		table->mans[index].forks[1] = &(table->forks[safe_range(index + 1)]);
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
		if ((man = &(table->mans[index]))->is & IS_MUTEX)
			pthread_mutex_destroy(&(man->mutex));
		if (man->is & IS_FORK)
			pthread_mutex_destroy(&(table->forks[index]));
		index++;
	}
	free(table->mans);
	free(table->forks);
}
