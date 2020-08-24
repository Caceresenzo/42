/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phmm_stop_await.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 12:00:29 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/11 12:00:29 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	phmm_await(t_table *table, sem_t *sem)
{
	int	index;

	index = -1;
	while (++index < table->child_count)
		sem_wait(sem);
}
