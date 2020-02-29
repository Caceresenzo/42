/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_ring_start.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:31:29 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 18:31:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int
	philosophers_ring_start(t_man *root)
{
	t_man	*next;

	next = root;
	while (1)
	{
		next->last_meal = x_millis();
		next->running = 1;
		next->wait_start = 0;
		if ((next = next->next) == root)
			break ;
	}
	return (0);
}
