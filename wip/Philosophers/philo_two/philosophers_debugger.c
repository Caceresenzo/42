/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_debugger.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 19:21:17 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 19:21:17 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	philosophers_debug_print_ring(t_man *root)
{
	t_man	*next;

	next = root;
	while (1)
	{
		printf("{\n");
		printf("\tman: #%d\n", next->id);
		printf("\tforks: #%p\n", next->forks);
		printf("}\n");
		if ((next = next->next) == root)
			break ;
	}
}
