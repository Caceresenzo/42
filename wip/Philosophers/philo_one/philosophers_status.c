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

pthread_mutex_t	g_status_update_mutex = (pthread_mutex_t){0};
int				g_someone_is_dead = 0;

void
	philosophers_status_mutex_init(void)
{
	pthread_mutex_init(&(g_status_update_mutex), NULL);
}

void
	philosophers_status_mutex_destroy(void)
{
	pthread_mutex_destroy(&(g_status_update_mutex));
}

void
	philosophers_status_update(t_man *man, t_man_state new_state)
{
	if (man->state == dead || (man->running == 0 && new_state != dead))
		return ;
	pthread_mutex_lock(&g_status_update_mutex);
	man->state = new_state;
	if (!(g_someone_is_dead))
	{
		x_putnbr(x_millis());
		x_putstr(" ");
		x_putnbr((long)0 + man->id);
		x_putstr(" ");
		x_putstr(g_man_states[new_state]);
		x_putstr("\n");
		g_someone_is_dead = new_state == dead;
	}
	pthread_mutex_unlock(&g_status_update_mutex);
}
