/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/12 13:54:38 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/12 13:54:38 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

sem_t
	*ph_sem_open(char *name, int def)
{
	sem_t	*sem;

	errno = 0;
	sem = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, def);
	if (sem == SEM_FAILED && errno == EEXIST)
	{
		sem_unlink(name);
		errno = 0;
		sem = sem_open(name, O_CREAT | O_EXCL, S_IRWXU, def);
	}
	return (sem);
}

void
	ph_sem_destroy(sem_t **sem, char *name)
{
	int	index;

	if (*sem != SEM_FAILED)
	{
		index = -1;
		errno = 0;
		while (++index < 10)
		{
			sem_post(*sem);
			if (ERANGE == errno)
				break ;
		}
		sem_close(*sem);
		if (name)
			sem_unlink(name);
		*sem = SEM_FAILED;
	}
}
