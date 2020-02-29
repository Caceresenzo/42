/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_ring_forks.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 19:11:15 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 19:11:15 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	philosophers_ring_forks(t_man *root, sem_t *forks)
{
	t_man	*next;

	next = root;
	while (1)
	{
		next->forks = forks;
		if ((next = next->next) == root)
			break ;
	}
}
