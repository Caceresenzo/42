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
		printf("\tfork left: #%d\n", next->fork_l->id);
		printf("\tfork right: #%d\n", next->fork_r->id);
		printf("}\n");
		if ((next = next->next) == root)
			break ;
	}
}
