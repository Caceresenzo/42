/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_ring_create.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:09:37 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 17:09:37 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_man
	*philosophers_ring_create(t_param param)
{
	t_man	*root;
	t_man	*next;
	t_man	*current;
	int		index;

	index = 0;
	if (!(root = philosophers_create(&index)))
		return (NULL);
	current = root;
	while (index < param.nbr_of_philo)
	{
		if (!(next = philosophers_create(&index)))
			break ;
		current->next = next;
		current = next;
	}
	current->next = root;
	return (root);
}
