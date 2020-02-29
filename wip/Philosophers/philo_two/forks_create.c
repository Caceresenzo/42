/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_create.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:06:30 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/29 14:06:30 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

sem_t
	*forks_create(char *name, int *err, int size)
{
	sem_t	*forks;

	errno = 0;
	sem_unlink(name);
	errno = 0;
	forks = sem_open(name, O_CREAT | O_EXCL, 0664, size);
	if (err != NULL)
		*err = errno;
	return (forks);
}
