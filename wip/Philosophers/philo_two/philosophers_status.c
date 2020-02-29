/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_status.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:55:24 by ecaceres          #+#    #+#             */
/*   Updated: 2020/02/27 17:55:24 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

sem_t		*g_status_update_sem = NULL;
int			g_someone_is_dead = 0;

void
	philosophers_status_sem_init(void)
{
	g_status_update_sem = forks_create(PROGRAM_SEM_UPDATE, NULL, 1);
}

void
	philosophers_status_sem_destroy(void)
{
	forks_destroy(PROGRAM_SEM_UPDATE, g_status_update_sem);
	g_status_update_sem = NULL;
}

void
	philosophers_status_update(t_man *man, t_man_state new_state)
{
	if (man->state == dead || (man->running == 0 && new_state != dead))
		return ;
	man->state = new_state;
	if (!g_someone_is_dead)
	{
		sem_wait(g_status_update_sem);
		x_putnbr(x_millis());
		x_putstr(" ");
		x_putnbr((long)0 + man->id);
		x_putstr(" ");
		x_putstr(g_man_states[new_state]);
		x_putstr("\n");
		sem_post(g_status_update_sem);
		g_someone_is_dead = new_state == dead;
	}
}
