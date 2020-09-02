/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 13:17:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/11 13:17:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void
	create(int *err, char *name, sem_t **ptr, int value)
{
	if (!*err && name)
	{
		errno = 0;
		*ptr = ph_sem_open(name, value);
		*err = errno;
	}
}

static void
	destroy(char *name, sem_t **ptr)
{
	ph_sem_destroy(ptr, name);
}

int
	phm_init(void)
{
	int err;

	err = 0;
	create(&err, SM_STDOUT, &g_sem_stdout, 1);
	create(&err, SM_MILLIS, &g_sem_millis, 1);
	create(&err, SM_FORKS, &g_sem_forks, g_params.nbr_of_philo);
	create(&err, SM_GRAB, &g_sem_grab, 1);
	return (err);
}

void
	phm_destroy(void)
{
	destroy(SM_STDOUT, &g_sem_stdout);
	destroy(SM_MILLIS, &g_sem_millis);
	destroy(SM_FORKS, &g_sem_forks);
	destroy(SM_GRAB, &g_sem_grab);
}
