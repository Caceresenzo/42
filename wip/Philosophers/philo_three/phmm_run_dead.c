/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phmm_run_dead.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 17:23:27 by ecaceres          #+#    #+#             */
/*   Updated: 2020/08/13 17:23:27 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void
	phmm_run_dead(t_table *table)
{
	sem_wait(g_sem_dead);
	if (!g_stopped)
		phmm_shout(table, g_sem_stop);
}
