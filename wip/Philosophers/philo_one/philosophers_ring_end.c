/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_ring_end.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 12:15:01 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/28 12:15:01 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int
	philosophers_ring_end(t_man *root, t_man *to_kill)
{
	t_man	*next;

	next = root;
	while (1)
	{
		next->running = 0;
		if ((next = next->next) == root)
			break ;
	}
	if (to_kill != NULL)
		philosophers_status_update(to_kill, dead);
	return (0);
}
