/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_ring_threader.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:31:29 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 18:31:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int
	philosophers_ring_threader(t_man *root)
{
	t_man	*next;
	int		err;

	next = root;
	while (1)
	{
		err = pthread_create(&(next->thr_id), NULL,
								(t_routine)philosophers_routine, next);
		if (err != 0)
			return (err);
		if ((next = next->next) == root)
			break ;
	}
	return (0);
}
