/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_ring_destroy.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 19:48:13 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 19:48:13 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int
	philosophers_ring_destroy(t_man *root)
{
	t_man	*next;
	t_man	*current;

	next = root;
	current = NULL;
	while (1)
	{
		next->fork_l = fork_destroy(next->fork_l);
		current = next;
		if ((next = next->next) == root)
			break ;
		current->next = NULL;
		philosophers_destroy(current);
	}
	philosophers_destroy(current);
	return (0);
}
