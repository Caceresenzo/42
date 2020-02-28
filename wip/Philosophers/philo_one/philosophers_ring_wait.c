/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_ring_wait.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 19:41:32 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 19:41:32 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int
	philosophers_ring_wait(t_man *root)
{
	t_man	*next;
	int		err;

	next = root;
	while (1)
	{
		err = pthread_join(next->thr_id, NULL);
		if (err != 0)
			return (err);
		if ((next = next->next) == root)
			break ;
	}
	return (0);
}
