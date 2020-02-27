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

int
	philosophers_ring_forks(t_param param, t_man *root)
{
	t_man	*next;
	t_man	*current;
	t_fork	*fork_l;
	t_fork	*fork_r;
	int		err;

	err = 0;
	next = root;
	fork_l = fork_create(&err);
	fork_r = NULL;
	if (err)
		return (err);
	while (1)
	{
		next->fork_l = fork_l;
		next->fork_r = fork_r;
		fork_r = fork_l;
		fork_l = fork_create(&err);
		if (err)
			return (err);
		current = next;
		if ((next = next->next) == root)
			break ;
	}
	root->fork_r = fork_r;
	return (0);
}
