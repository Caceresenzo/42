/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_create.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:14:50 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 17:14:50 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_man
	*philosophers_create(int *index)
{
	t_man	*man;

	if ((man = malloc(sizeof(t_man))))
	{
		x_memset(man, 0, sizeof(t_man));
		man->id = *index + 1;
		man->running = 0;
		*index += 1;
	}
	return (man);
}
