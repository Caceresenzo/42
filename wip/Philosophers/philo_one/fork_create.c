/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 19:04:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 19:04:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int g_x = 0;

t_fork
	*fork_create(int *err)
{
	t_fork	*fork;

	*err = 0;
	if ((fork = malloc(sizeof(t_fork))))
	{
		x_memset(fork, 0, sizeof(t_fork));
		fork->id = g_x++;
		*err = pthread_mutex_init(&(fork->mutex), NULL);
		if (*err)
		{
			free(fork);
			fork = NULL;
		}
	}
	return (fork);
}
