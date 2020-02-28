/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 19:04:18 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 19:04:18 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_fork
	*fork_destroy(t_fork *fork)
{
	if (fork != NULL)
	{
		pthread_mutex_destroy(&(fork->mutex));
		free(fork);
	}
	return (fork = NULL);
}
