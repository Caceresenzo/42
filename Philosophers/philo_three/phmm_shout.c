/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phmm_shout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 17:26:08 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/13 17:26:08 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	phmm_shout(t_table *table, sem_t *sem)
{
	int	index;

	index = -1;
	while (++index < table->child_count)
		sem_post(sem);
}
