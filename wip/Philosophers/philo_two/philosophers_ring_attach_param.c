/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_ring_attach_param.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 11:10:06 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/28 11:10:06 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	philosophers_ring_attach_param(t_man *root, t_param *param)
{
	t_man	*next;

	next = root;
	while (1)
	{
		next->param = param;
		if ((next = next->next) == root)
			break ;
	}
}
